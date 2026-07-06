#ifndef METAFIDER_IOMANAGER_H
#define METAFIDER_IOMANAGER_H

#include <expected>
#include <fstream>
#include <ios>
#include <string>
#include <vector>

enum class IOError {
    OpenError,
    ReadError,
    OutOfRange,
};

class IOManager {
public:
    IOManager() = default;

    static std::expected<std::vector<uint8_t>, IOError> LoadMetadata(const std::string &metadata_path);

    template <typename T>
    std::expected<T, IOError> ReadValue(const std::vector<uint8_t>& metadata, size_t offset);

    template <typename T>
    std::expected<std::vector<T>, IOError> ReadArray(const std::vector<uint8_t>& buffer, size_t offset, size_t count);
};


#endif //METAFIDER_IOMANAGER_H
