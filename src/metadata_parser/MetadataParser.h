#ifndef METAFIDER_METADATAPARSER_H
#define METAFIDER_METADATAPARSER_H

#include <expected>
#include <vector>

#include "../heuristics/Heuristics.h"
#include "../io_manager/IOManager.h"

class MetadataParser {
public:
    MetadataParser(IOManager& io_manager, Heuristics& heuristics, const std::vector<uint8_t>& metadata);

    std::expected<std::vector<uint32_t>, IOE::IOError> ParseFields(size_t header_size) const;

    std::expected<std::vector<uint32_t>, IOE::IOError> ParseOffsets(
        const std::vector<uint32_t>& fields
    ) const;
private:
    IOManager& m_io_manager;
    Heuristics& m_heuristics;
    const std::vector<uint8_t>& m_metadata;
};


#endif //METAFIDER_METADATAPARSER_H
