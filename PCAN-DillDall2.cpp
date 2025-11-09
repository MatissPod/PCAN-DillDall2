#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <csignal>
#include <iomanip>
#include <windows.h>
#include <PCANBasic.h>

static char FD_BITRATE_CFG[] =
    "f_clock_mhz=80,"
    "nom_brp=1,nom_tseg1=63,nom_tseg2=16,nom_sjw=16,"
    "data_brp=1,data_tseg1=11,data_tseg2=4,data_sjw=4";
std::atomic<bool> keepRunning(true);

void signalHandler(int signum) {
    keepRunning = false;
}

int main() {
    TPCANHandle pcanHandle = PCAN_USBBUS1;

    // Initialize
    CAN_Uninitialize(pcanHandle);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    TPCANStatus status = CAN_InitializeFD(pcanHandle, FD_BITRATE_CFG);
    if (status != PCAN_ERROR_OK) {
        std::cerr << "Failed to initialize PCAN: 0x" << std::hex << status << std::dec << std::endl;
        return 1;
    }

    // Enable listen-only mode
    BYTE listenOnly = PCAN_PARAMETER_ON;
    CAN_SetValue(pcanHandle, PCAN_LISTEN_ONLY, &listenOnly, sizeof(listenOnly));

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
            if (errorCount % 50 == 1) {
                std::cerr << "Bus errors detected (" << errorCount << " total)\n";
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