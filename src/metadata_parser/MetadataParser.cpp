#include "MetadataParser.h"

MetadataParser::MetadataParser(IOManager& io_manager, const std::vector<uint8_t>& metadata)
    : m_io_manager(io_manager), m_metadata(metadata) {}

std::expected<std::vector<uint32_t>, IOError> MetadataParser::ParseFields(const size_t header_size) const {
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
