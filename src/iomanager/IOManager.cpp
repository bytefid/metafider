#include "IOManager.h"

#include <fstream>

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