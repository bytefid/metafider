#ifndef METAFIDER_IOMANAGER_H
#define METAFIDER_IOMANAGER_H

#include <expected>
#include <string>
#include <string_view>
#include <vector>
#include <cstring>


namespace IO {
    enum class Error {
        OpenError,
        ReadError,
        OutOfRange,
    };

    static constexpr std::string_view ToCString(const Error error) {
        switch (error) {
            case Error::OpenError:   return "Failed to open file (OpenError)";
            case Error::ReadError:   return "Failed to read file data (ReadError)";
            case Error::OutOfRange:  return "Attempted to read out of bounds (OutOfRange)";
            default:                   return "Unknown IO Error";
        }
    }
}


class IOManager {
public:
    IOManager() = default;

    std::expected<std::vector<uint8_t>, IO::Error> LoadMetadata(const std::string &metadata_path);

    template <typename T>
    std::expected<T, IO::Error> ReadValue(const std::vector<uint8_t>& metadata, const size_t offset) const {
        if (offset + sizeof(T) > metadata.size()) {
            return std::unexpected(IO::Error::OutOfRange);
        }
        T value;
        std::memcpy(&value, metadata.data() + offset, sizeof(T));
        return value;
    }

    template <typename T>
    std::expected<std::vector<T>, IO::Error> ReadArray(const std::vector<uint8_t>& metadata, const size_t offset, size_t count) const {
        const size_t total_size = count * sizeof(T);
        if (offset + total_size > metadata.size()) {
            return std::unexpected(IO::Error::OutOfRange);
        }
        std::vector<T> result(count);
        std::memcpy(result.data(), metadata.data() + offset, total_size);
        return result;
    }
};


#endif //METAFIDER_IOMANAGER_H
