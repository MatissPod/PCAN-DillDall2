#include <csignal>
#include <iostream>
#include <thread>
#include <atomic>
#include <windows.h>  // Required for Windows types like DWORD, BYTE, etc.
#include "PCANBasic.h"  // PEAK PCANBasic API

// =====================
// Configuration
// =====================
static char FD_BITRATE_CFG[] =
    "f_clock=80000000,"
    "nom_brp=10,nom_tseg1=5,nom_tseg2=2,nom_sjw=1,"
    "data_brp=2,data_tseg1=7,data_tseg2=2,data_sjw=1";



// =====================
// Main program
// =====================
int main() {
  
    TPCANHandle pcanHandle = PCAN_USBBUS1;  // use first USB PCAN device
    bool running = false;

    // Initialize PCAN-FD channel
    TPCANStatus status = CAN_InitializeFD(pcanHandle, FD_BITRATE_CFG);
    if (status != PCAN_ERROR_OK) {
        std::cerr << "Error initializing PCAN FD channel: 0x"
                  << std::hex << status << std::dec << std::endl;
        return 1;
    }

    std::cout << "PCAN FD channel initialized successfully.\n";
    running = true;

    std::atomic<bool> keepRunning(true);

    // Handle Ctrl+C gracefully
    std::signal(SIGINT, [](int){ 
        std::cout << "\nStopping reader...\n"; 
        std::exit(0); 
    });

    // Main loop: read messages periodically
    while (keepRunning) {
        if (!running) {
            std::cerr << "Error: PCAN FD channel is not running.\n";
            break;
        }

        TPCANMsgFD canMsg;
        TPCANTimestampFD timeStamp;

        // Try to read a message
        TPCANStatus readStatus = CAN_ReadFD(pcanHandle, &canMsg, &timeStamp);

        if (readStatus == PCAN_ERROR_QRCVEMPTY) {
            // no messages available, small delay
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }
        else if (readStatus != PCAN_ERROR_OK) {
            std::cerr << "Error reading message from PCAN: 0x"
                      << std::hex << readStatus << std::dec << std::endl;
            break;
        }

        // Print the message info
        std::cout << "[PCAN] ID: 0x" << std::hex << (canMsg.ID & 0x1FFFFFFF)
                  << std::dec << ", DLC: " << static_cast<int>(canMsg.DLC)
                  << ", Data: ";

        for (int i = 0; i < canMsg.DLC; ++i) {
            std::cout << std::hex << static_cast<int>(canMsg.DATA[i] & 0xFF) << " ";
        }

        std::cout << std::dec << std::endl;
    }

    // Cleanup
    if (running) {
        CAN_Uninitialize(pcanHandle);
        std::cout << "PCAN interface shut down.\n";
    }

    return 0;
}