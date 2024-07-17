cmake_minimum_required(VERSION 3.15)
project(Rakab)

set(CMAKE_C_STANDARD 11) # Requires C11 standard
set(CMAKE_C_COMPILER "C:/w64devkit/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/w64devkit/bin/g++.exe")

add_subdirectory(./src)
