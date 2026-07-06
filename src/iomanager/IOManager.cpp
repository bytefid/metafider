#include "IOManager.h"

std::expected<std::vector<uint8_t>, IOError> IOManager::LoadMetadata(const std::string &metadata_path) {
    std::ifstream file(metadata_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        return std::unexpected(IOError::OpenError);
    }

    const std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);

    if (!file.read(reinterpret_cast<char *>(buffer.data()), size)) {
        return std::unexpected(IOError::ReadError);
    }


    return buffer;
}


template <typename T>
std::expected<T, IOError> IOManager::ReadValue(const std::vector<uint8_t>& metadata, const size_t offset) {
    if (offset + sizeof(T) > metadata.size()) {
        return std::unexpected(IOError::OutOfRange);
    }
    T value;
    std::memcpy(&value, metadata.data() + offset, sizeof(T));
    return value;
}


template <typename T>
std::expected<std::vector<T>, IOError> IOManager::ReadArray(const std::vector<uint8_t>& buffer, const size_t offset, size_t count) {
    const size_t total_size = count * sizeof(T);
    if (offset + total_size > buffer.size()) {
        return std::unexpected(IOError::OutOfRange);
    }
    std::vector<T> result(count);
    std::memcpy(result.data(), buffer.data() + offset, total_size);
    return result;
}