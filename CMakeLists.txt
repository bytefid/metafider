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
        src/heuristics/Heuristics.cpp
        src/heuristics/Heuristics.h
        src/metafider_app/MetafiderApp.cpp
        src/metafider_app/MetafiderApp.h
        src/config/ConfigLoader.cpp
        src/config/ConfigLoader.h
)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(metafider PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(metafider PRIVATE ${CMAKE_SOURCE_DIR}/src)