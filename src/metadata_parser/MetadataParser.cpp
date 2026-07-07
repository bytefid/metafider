#include "MetadataParser.h"

MetadataParser::MetadataParser(IOManager& io_manager, Heuristics& heuristics, const std::vector<uint8_t>& metadata)
    : m_io_manager(io_manager), m_heuristics(heuristics), m_metadata(metadata) {}

std::expected<std::vector<uint32_t>, IOE::IOError> MetadataParser::ParseFields(const size_t header_size) const {
    std::vector<uint32_t> fields;

    for (size_t i = 0; i + 4 <= header_size && i + 4 <= m_metadata.size(); i += 4) {
        const auto field = m_io_manager.ReadValue<uint32_t>(m_metadata, i);
        if (!field.has_value()) {
            return std::unexpected(field.error());
        }
        fields.push_back(field.value());
    }

    return fields;
}

std::expected<std::vector<uint32_t>, IOE::IOError> MetadataParser::ParseOffsets(
    const std::vector<uint32_t>& fields
) const {
    std::vector<uint32_t> probable_offsets;
    probable_offsets.reserve(fields.size());

    for (const uint32_t field : fields) {
        if (m_heuristics.IsProbableOffset(m_metadata, field)) {
            probable_offsets.push_back(field);
        }
    }

    return probable_offsets;
}