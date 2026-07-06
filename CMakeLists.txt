cmake_minimum_required(VERSION 4.2)
project(metafider CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(metafider src/main.cpp
        src/iomanager/IOManager.cpp
        src/iomanager/IOManager.h
)