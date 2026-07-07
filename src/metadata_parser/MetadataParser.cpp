#include "MetadataParser.h"

#include <algorithm>

MetadataParser::MetadataParser(IOManager& io_manager, Heuristics& heuristics, std::shared_ptr<const std::vector<uint8_t>> metadata)
    : m_io_manager(io_manager), m_heuristics(heuristics), m_metadata(std::move(metadata)) {}

MetadataParsed::data MetadataParser::GetParsedData() const { return m_data; }

std::expected<bool, IO::Error> MetadataParser::ParseFields(const size_t header_size) {
    std::vector<uint32_t> fields;

    for (size_t i = 0; i + 4 <= header_size && i + 4 <= m_metadata->size(); i += 4) {
        const auto field = m_io_manager.ReadValue<uint32_t>(*m_metadata, i);
        if (!field.has_value()) {
            return std::unexpected(field.error());
        }
        fields.push_back(field.value());
    }

    m_data.fields = fields;
    return true;
}

std::expected<bool, IO::Error> MetadataParser::ParseOffsets(const std::vector<uint32_t>& fields) {
    std::vector<uint32_t> probable_offsets;
    probable_offsets.reserve(fields.size());

    for (const uint32_t field : fields) {
        if (m_heuristics.IsProbableOffset(*m_metadata, field)) {
            probable_offsets.push_back(field);
        }
    }

    std::sort(probable_offsets.begin(), probable_offsets.end());
    const auto last = std::unique(probable_offsets.begin(), probable_offsets.end());
    probable_offsets.erase(last, probable_offsets.end());

    m_data.offsets = probable_offsets;
    return true;
}