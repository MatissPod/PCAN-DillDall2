#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <csignal>
#include <iomanip>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif
#include <PCANBasic.h>

static char FD_BITRATE_CFG[] =
    "f_clock=80000000,"
    "nom_brp=10,nom_tseg1=5,nom_tseg2=2,nom_sjw=1,"
    "data_brp=2,data_tseg1=5,data_tseg2=2,data_sjw=1";
std::atomic<bool> keepRunning(true);

void signalHandler(int signum) {
    keepRunning = false;
}

static void printErrorText(const char* prefix, TPCANStatus status)
{
    char buffer[256] = {0};
    if (CAN_GetErrorText(status, 0x09 /* English */, buffer) == PCAN_ERROR_OK) {
        std::cerr << prefix << " (" << std::hex << status << std::dec << ") -> " << buffer << std::endl;
    } else {
        std::cerr << prefix << " (0x" << std::hex << status << std::dec << ")" << std::endl;
    }
}

static void listAttachedChannels()
{
    // Query count
    DWORD count = 0;
    TPCANStatus s = CAN_GetValue(PCAN_NONEBUS, PCAN_ATTACHED_CHANNELS_COUNT, &count, sizeof(count));
    if (s != PCAN_ERROR_OK || count == 0) {
        std::cerr << "No attached PCAN channels reported (status=" << std::hex << s << std::dec << ")" << std::endl;
        return;
    }

    std::vector<TPCANChannelInformation> channels(count);
    DWORD bufSize = static_cast<DWORD>(channels.size() * sizeof(TPCANChannelInformation));
    s = CAN_GetValue(PCAN_NONEBUS, PCAN_ATTACHED_CHANNELS, channels.data(), bufSize);
    if (s != PCAN_ERROR_OK) {
        std::cerr << "Failed to get attached channels (status=0x" << std::hex << s << std::dec << ")" << std::endl;
        return;
    }

    std::cout << "Attached PCAN channels (" << channels.size() << "):" << std::endl;
    for (const auto& ch : channels) {
        std::cout << "  handle=0x" << std::hex << ch.channel_handle << std::dec
                  << ", device_type=" << static_cast<int>(ch.device_type)
                  << ", ctrl=" << static_cast<int>(ch.controller_number)
                  << ", features=0x" << std::hex << ch.device_features << std::dec
                  << ", name='" << ch.device_name << "'"
                  << ", id=" << ch.device_id
                  << ", condition=" << ch.channel_condition
                  << std::endl;
    }
}

int main() {
    TPCANHandle pcanHandle = PCAN_USBBUS1;

    // Initialize
    CAN_Uninitialize(pcanHandle);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    TPCANStatus status = CAN_InitializeFD(pcanHandle, FD_BITRATE_CFG);
    if (status != PCAN_ERROR_OK) {
        printErrorText("Failed to initialize PCAN", status);
        std::cerr << "Hint: This often means the kernel driver is missing or the channel handle doesn't match. Listing detected channels..." << std::endl;
        listAttachedChannels();
        return 1;
    }

    // Enable listen-only mode
    BYTE listenOnly = PCAN_PARAMETER_ON;
    TPCANStatus setRes = CAN_SetValue(pcanHandle, PCAN_LISTEN_ONLY, &listenOnly, sizeof(listenOnly));
    if (setRes != PCAN_ERROR_OK) {
        printErrorText("Failed to enable listen-only", setRes);
    }

    // Show configured FD bitrates (nominal/data)
    char brInfo[128] = {0};
    if (CAN_GetValue(pcanHandle, PCAN_BITRATE_INFO_FD, brInfo, sizeof(brInfo)) == PCAN_ERROR_OK) {
        std::cout << "Configured FD bitrate: " << brInfo << std::endl;
    }

    std::cout << "CAN FD Reader Started (1M/5M)\n";
    std::cout << "Press Ctrl+C to stop\n\n";

    std::signal(SIGINT, signalHandler);

    int messageCount = 0;
    int errorCount = 0;

    while (keepRunning) {
        TPCANMsgFD canMsg;
        TPCANTimestampFD timeStamp;

        TPCANStatus readStatus = CAN_ReadFD(pcanHandle, &canMsg, &timeStamp);

        if (readStatus == PCAN_ERROR_QRCVEMPTY) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }
        
        if (readStatus == PCAN_ERROR_OK) {
            messageCount++;

            // Print message
            std::cout << "[" << messageCount << "] ID: 0x" 
                      << std::hex << std::setw(8) << std::setfill('0')
                      << (canMsg.ID & 0x1FFFFFFF)
                      << std::dec << " | DLC: " << static_cast<int>(canMsg.DLC)
                      << " | ";

            for (int i = 0; i < canMsg.DLC && i < 64; ++i) {
                std::cout << std::hex << std::setw(2) << std::setfill('0') 
                          << static_cast<int>(canMsg.DATA[i]) << " ";
            }
            std::cout << std::dec << std::endl;
        }
        else {
            errorCount++;
            
            // Only show errors occasionally to avoid spam
            if (errorCount % 20 == 1) {
                std::cerr << "Bus errors detected (" << errorCount << " total)\n";
                printErrorText("Read error", readStatus);
                TPCANStatus st = CAN_GetStatus(pcanHandle);
                printErrorText("Channel status", st);
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    // Cleanup
    CAN_Uninitialize(pcanHandle);
    std::cout << "\nStopped. Messages: " << messageCount 
              << " | Errors: " << errorCount << std::endl;

    return 0;
}