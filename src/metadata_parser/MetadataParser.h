#ifndef METAFIDER_METADATAPARSER_H
#define METAFIDER_METADATAPARSER_H

#include <expected>
#include <vector>
#include "../io_manager/IOManager.h"

struct OffsetHeuristics {
    uint32_t divisible_by = 4;
    uint32_t greater_than_value = 8192;
    uint32_t size_divisor = 8;
    bool require_in_bounds = true;
};

class MetadataParser {
public:
    MetadataParser(IOManager& io_manager, const std::vector<uint8_t>& metadata);

    std::expected<std::vector<uint32_t>, IOE::IOError> ParseFields(size_t header_size) const;

    std::expected<std::vector<uint32_t>, IOE::IOError> ParseOffsets(
        const std::vector<uint32_t>& fields,
        const OffsetHeuristics& heuristics
    ) const;
private:
    IOManager& m_io_manager;
    const std::vector<uint8_t>& m_metadata;
};


#endif //METAFIDER_METADATAPARSER_H
