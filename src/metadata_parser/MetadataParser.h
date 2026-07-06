#ifndef METAFIDER_METADATAPARSER_H
#define METAFIDER_METADATAPARSER_H

#include <expected>
#include <vector>
#include "../io_manager/IOManager.h"

enum class ParserError {

};

class MetadataParser {
public:
    MetadataParser(IOManager& io_manager, const std::vector<uint8_t>& metadata);

    std::expected<std::vector<uint32_t>, IOError> ParseFields(size_t header_size) const;

private:
    IOManager& m_io_manager;
    const std::vector<uint8_t>& m_metadata;
};


#endif //METAFIDER_METADATAPARSER_H
