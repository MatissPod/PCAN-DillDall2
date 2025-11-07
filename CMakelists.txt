cmake_minimum_required(VERSION 3.10)

project(PCAN-DillDall2)

find_package(fmt CONFIG REQUIRED)

find_package(pcan-basic REQUIRED)

add_executable(PCAN-DillDall2 PCAN-DillDall2.cpp)

target_link_libraries(PCAN-DillDall2 
PRIVATE 
pcan-basic
fmt::fmt)