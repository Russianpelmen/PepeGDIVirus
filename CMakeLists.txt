cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

project("GdiVirus")

add_executable("PepeGdiVirus" WIN32 "main.cpp" "resource.h" "resouse.rc")
