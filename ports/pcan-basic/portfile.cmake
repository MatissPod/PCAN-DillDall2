message(STATUS "pcan-basic: Starting portfile execution for x64-windows")

# Determine architecture-specific paths
if(VCPKG_TARGET_ARCHITECTURE STREQUAL "x64")
    set(ARCH_FOLDER "x64")
    message(STATUS "pcan-basic: Target architecture is x64")
elseif(VCPKG_TARGET_ARCHITECTURE STREQUAL "x86")
    set(ARCH_FOLDER "x86")
    message(STATUS "pcan-basic: Target architecture is x86")
elseif(VCPKG_TARGET_ARCHITECTURE STREQUAL "arm64")
    set(ARCH_FOLDER "ARM64")
    message(STATUS "pcan-basic: Target architecture is ARM64")
else()
    message(FATAL_ERROR "pcan-basic: Unsupported architecture ${VCPKG_TARGET_ARCHITECTURE}")
endif()

# --- Define download details ---
set(API_URL "https://www.peak-system.com/fileadmin/media/files/PCAN-Basic.zip")
set(API_ZIP "PCANBasic_Windows.zip")
message(STATUS "pcan-basic: Download details set - URL: ${API_URL}, ZIP: ${API_ZIP}")

# --- Define paths ---
set(DOWNLOAD_DIR "${CURRENT_PACKAGES_DIR}/download")
message(STATUS "pcan-basic: Creating download directory: ${DOWNLOAD_DIR}")
file(MAKE_DIRECTORY "${DOWNLOAD_DIR}")
set(ZIP_PATH "${DOWNLOAD_DIR}/${API_ZIP}")
message(STATUS "pcan-basic: ZIP will be downloaded to: ${ZIP_PATH}")

# --- Download the zipfile ---
message(STATUS "pcan-basic: Downloading zip from ${API_URL} to ${ZIP_PATH}")
file(DOWNLOAD
    "${API_URL}"
    "${ZIP_PATH}"
    SHOW_PROGRESS
)
message(STATUS "pcan-basic: ZIP downloaded successfully.")

# --- Verify download ---
if(NOT EXISTS "${ZIP_PATH}")
    message(FATAL_ERROR "pcan-basic: ZIP not found at ${ZIP_PATH}")
else()
    file(SIZE "${ZIP_PATH}" ZIP_SIZE)
    message(STATUS "pcan-basic: Downloaded zip size: ${ZIP_SIZE} bytes")
endif()

# --- Extract the zip ---
set(EXTRACT_DIR "${CURRENT_PACKAGES_DIR}/src")
message(STATUS "pcan-basic: Creating extraction directory: ${EXTRACT_DIR}")
file(MAKE_DIRECTORY "${EXTRACT_DIR}")
message(STATUS "pcan-basic: Extracting zip to ${EXTRACT_DIR}")
file(ARCHIVE_EXTRACT
    INPUT "${ZIP_PATH}"
    DESTINATION "${EXTRACT_DIR}"
)
message(STATUS "pcan-basic: Extraction completed.")

# --- Detect the extracted folder ---
# List contents to see what was extracted
file(GLOB EXTRACTED_ITEMS "${EXTRACT_DIR}/*")
message(STATUS "pcan-basic: Contents of extract dir: ${EXTRACTED_ITEMS}")

# Check if files were extracted directly to EXTRACT_DIR or into a subdirectory
set(API_DIR "")

# First check if Include and x64 are directly in EXTRACT_DIR
if(EXISTS "${EXTRACT_DIR}/Include" AND EXISTS "${EXTRACT_DIR}/x64")
    set(API_DIR "${EXTRACT_DIR}")
    message(STATUS "pcan-basic: Files extracted directly to root, using: ${API_DIR}")
else()
    # Otherwise, look for a subdirectory containing the PCAN files
    foreach(ITEM ${EXTRACTED_ITEMS})
        if(IS_DIRECTORY "${ITEM}")
            get_filename_component(FOLDER_NAME "${ITEM}" NAME)
            message(STATUS "pcan-basic: Checking directory: ${FOLDER_NAME}")
            # Check if this looks like the PCAN directory (contains Include or x64 folder)
            if(EXISTS "${ITEM}/Include" AND EXISTS "${ITEM}/x64")
                set(API_DIR "${ITEM}")
                message(STATUS "pcan-basic: Using API directory: ${API_DIR}")
                break()
            endif()
        endif()
    endforeach()
endif()

if(API_DIR STREQUAL "")
    message(FATAL_ERROR "pcan-basic: Could not find PCAN-Basic directory in extracted files")
endif()

message(STATUS "pcan-basic: API directory set to: ${API_DIR}")

# --- Define include / lib / bin locations ---
set(INCLUDE_DIR "${API_DIR}/Include")
set(LIB_DIR     "${API_DIR}/${ARCH_FOLDER}/VC_LIB")
set(BIN_DIR     "${API_DIR}/${ARCH_FOLDER}")

message(STATUS "pcan-basic: Include dir: ${INCLUDE_DIR}")
message(STATUS "pcan-basic: Lib dir:     ${LIB_DIR}")
message(STATUS "pcan-basic: Bin dir:     ${BIN_DIR}")

# Verify directories exist
if(NOT EXISTS "${INCLUDE_DIR}")
    message(WARNING "pcan-basic: Include directory does not exist: ${INCLUDE_DIR}")
endif()
if(NOT EXISTS "${LIB_DIR}")
    message(WARNING "pcan-basic: Lib directory does not exist: ${LIB_DIR}")
endif()
if(NOT EXISTS "${BIN_DIR}")
    message(WARNING "pcan-basic: Bin directory does not exist: ${BIN_DIR}")
endif()

# --- Install headers ---
file(GLOB PCAN_HEADERS "${INCLUDE_DIR}/*.h")
if(PCAN_HEADERS)
    file(INSTALL FILES ${PCAN_HEADERS}
         DESTINATION "${CURRENT_PACKAGES_DIR}/include")
    message(STATUS "pcan-basic: Header files installed successfully.")
else()
    message(WARNING "pcan-basic: No header files found in ${INCLUDE_DIR}")
endif()

# --- Install library (.lib) ---
file(GLOB PCAN_LIBS "${LIB_DIR}/*.lib")
if(PCAN_LIBS)
    file(INSTALL FILES ${PCAN_LIBS}
         DESTINATION "${CURRENT_PACKAGES_DIR}/lib")
    # Also install to debug lib (PCAN doesn't provide separate debug builds)
    file(INSTALL FILES ${PCAN_LIBS}
         DESTINATION "${CURRENT_PACKAGES_DIR}/debug/lib")
    message(STATUS "pcan-basic: Lib files installed successfully.")
else()
    message(FATAL_ERROR "pcan-basic: No .lib files found in ${LIB_DIR}")
endif()

# --- Install binary (.dll) ---
file(GLOB PCAN_DLLS "${BIN_DIR}/*.dll")
if(PCAN_DLLS)
    file(INSTALL FILES ${PCAN_DLLS}
         DESTINATION "${CURRENT_PACKAGES_DIR}/bin")
    # Also install to debug bin (PCAN doesn't provide separate debug builds)
    file(INSTALL FILES ${PCAN_DLLS}
         DESTINATION "${CURRENT_PACKAGES_DIR}/debug/bin")
    message(STATUS "pcan-basic: DLL files installed successfully.")
else()
    message(WARNING "pcan-basic: No .dll files found in ${BIN_DIR}")
endif()

# --- Create CMake config file for consumer projects ---
set(CONFIG_PATH "${CURRENT_PACKAGES_DIR}/share/pcan-basic/pcan-basic-config.cmake")
file(WRITE "${CONFIG_PATH}" "
# This file was auto-generated by the pcan-basic portfile

if(POLICY CMP0111)
  cmake_policy(SET CMP0111 NEW)
endif()

# Set include and lib paths
set(PCAN_BASIC_INCLUDE_DIR \"\${CMAKE_CURRENT_LIST_DIR}/../../include\")
set(PCAN_BASIC_LIB_DIR     \"\${CMAKE_CURRENT_LIST_DIR}/../../lib\")

# Create imported target
if(NOT TARGET pcan-basic)
    add_library(pcan-basic SHARED IMPORTED)
    set_target_properties(pcan-basic PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES \"\${PCAN_BASIC_INCLUDE_DIR}\"
        IMPORTED_IMPLIB \"\${PCAN_BASIC_LIB_DIR}/PCANBasic.lib\"
        IMPORTED_LOCATION \"\${CMAKE_CURRENT_LIST_DIR}/../../bin/PCANBasic.dll\"
    )
    # cfg-specific properties
    set_property(TARGET pcan-basic APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
    set_target_properties(pcan-basic PROPERTIES 
        IMPORTED_IMPLIB_RELEASE \"\${PCAN_BASIC_LIB_DIR}/PCANBasic.lib\"
        IMPORTED_LOCATION_RELEASE \"\${CMAKE_CURRENT_LIST_DIR}/../../bin/PCANBasic.dll\"
    )
    # Debug configuration (same as release since PCAN doesn't provide debug builds)
    set_property(TARGET pcan-basic APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
    set_target_properties(pcan-basic PROPERTIES 
        IMPORTED_IMPLIB_DEBUG \"\${CMAKE_CURRENT_LIST_DIR}/../../debug/lib/PCANBasic.lib\"
        IMPORTED_LOCATION_DEBUG \"\${CMAKE_CURRENT_LIST_DIR}/../../debug/bin/PCANBasic.dll\"
    )
endif()
")
message(STATUS "pcan-basic: Config file written to ${CONFIG_PATH}")

# Handle copyright
file(INSTALL 
    FILES "${API_DIR}/ReadMe.txt"
    DESTINATION "${CURRENT_PACKAGES_DIR}/share/pcan-basic"
    RENAME copyright
)
message(STATUS "pcan-basic: Copyright file installed.")

message(STATUS "pcan-basic: Windows portfile execution completed successfully")