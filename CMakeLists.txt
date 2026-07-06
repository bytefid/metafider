cmake_minimum_required(VERSION 4.2)
project(metafider CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(metafider src/main.cpp
        src/io_manager/IOManager.cpp
        src/io_manager/IOManager.h
        src/metadata_parser/MetadataParser.cpp
        src/metadata_parser/MetadataParser.h
)