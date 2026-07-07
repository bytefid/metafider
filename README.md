# metafider

A C++23 utility designed for parsing binary metadata files and extracting candidate offsets using configurable heuristic rules.

## Features

- **Safe Binary I/O**: Exception-free reading of primitive types and arrays using `std::expected` for structured error handling.
- **Decoupled Heuristics**: Isolated evaluation engine to screen and filter fields based on divisibility, minimum value thresholds, and dynamic file size boundaries.
- **Modern C++23 Standards**: Leverages C++23 library features such as `std::expected` and `std::print`.

## Requirements

- C++23 compliant compiler (e.g., Clang 16+, GCC 13+, MSVC 19.38+)
- CMake 4.2 or higher

## Directory Structure

- `src/io_manager/`: Utility classes for loading files and safe byte-level parsing.
- `src/metadata_parser/`: Parser implementation for extracting structured fields from binary sources.
- `src/heuristics/`: Isolated heuristics evaluation logic.
- `src/main.cpp`: Main executable entry point.

## Building the Project

Configure and compile the project using CMake:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .