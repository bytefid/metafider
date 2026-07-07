#ifndef METAFIDER_METADATAPARSER_H
#define METAFIDER_METADATAPARSER_H

#include <expected>
#include <memory>
#include <vector>

#include "heuristics/Heuristics.h"
#include "io_manager/IOManager.h"


namespace MetadataParsed {
    struct data {
        std::vector<uint32_t> fields;
        std::vector<uint32_t> offsets;
    };
}


class MetadataParser {
public:
    MetadataParser(IOManager& io_manager, Heuristics& heuristics, std::shared_ptr<const std::vector<uint8_t>> metadata);
    MetadataParsed::data GetParsedData() const;

    std::expected<bool, IO::Error> ParseFields(size_t header_size);
    std::expected<bool, IO::Error> ParseOffsets(const std::vector<uint32_t>& fields);
private:
    IOManager& m_io_manager;
    Heuristics& m_heuristics;
    std::shared_ptr<const std::vector<uint8_t>> m_metadata;
    MetadataParsed::data m_data;
};


#endif //METAFIDER_METADATAPARSER_H
