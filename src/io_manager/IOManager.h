#ifndef METAFIDER_IOMANAGER_H
#define METAFIDER_IOMANAGER_H

#include <expected>
#include <ios>
#include <string>
#include <vector>

enum class IOError {
    OpenError,
    ReadError,
    OutOfRange,
};

static constexpr std::string_view ToCString(const IOError error) {
    switch (error) {
        case IOError::OpenError:   return "Failed to open file (OpenError)";
        case IOError::ReadError:   return "Failed to read file data (ReadError)";
        case IOError::OutOfRange:  return "Attempted to read out of bounds (OutOfRange)";
        default:                   return "Unknown IO Error";
    }
}

class IOManager {
public:
    IOManager() = default;

    std::expected<std::vector<uint8_t>, IOError> LoadMetadata(const std::string &metadata_path);

    template <typename T>
    std::expected<T, IOError> ReadValue(const std::vector<uint8_t>& metadata, const size_t offset) {
        if (offset + sizeof(T) > metadata.size()) {
            return std::unexpected(IOError::OutOfRange);
        }
        T value;
        std::memcpy(&value, metadata.data() + offset, sizeof(T));
        return value;
    }

    template <typename T>
    std::expected<std::vector<T>, IOError> ReadArray(const std::vector<uint8_t>& metadata, const size_t offset, size_t count) {
        const size_t total_size = count * sizeof(T);
        if (offset + total_size > metadata.size()) {
            return std::unexpected(IOError::OutOfRange);
        }
        std::vector<T> result(count);
        std::memcpy(result.data(), buffer.data() + offset, total_size);
        return result;
    }
};


#endif //METAFIDER_IOMANAGER_H
