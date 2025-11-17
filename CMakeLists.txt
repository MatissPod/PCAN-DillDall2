cmake_minimum_required(VERSION 3.10)
project(PCAN-DillDall2 LANGUAGES C CXX)

find_package(fmt CONFIG REQUIRED)

add_executable(PCAN-DillDall2
    PCAN-DillDall2.cpp
)

target_link_libraries(PCAN-DillDall2
    PRIVATE
        fmt::fmt
        ${CMAKE_SOURCE_DIR}/libPCBUSB.0.12.2.dylib
)

target_include_directories(PCAN-DillDall2 PRIVATE ${CMAKE_SOURCE_DIR})