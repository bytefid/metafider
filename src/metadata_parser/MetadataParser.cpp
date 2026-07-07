#include "MetadataParser.h"

MetadataParser::MetadataParser(IOManager& io_manager, const std::vector<uint8_t>& metadata)
    : m_io_manager(io_manager), m_metadata(metadata) {}

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
    const std::vector<uint32_t>& fields,
    const OffsetHeuristics& heuristics
) const {
    std::vector<uint32_t> probable_offsets;
    probable_offsets.reserve(fields.size());

    for (const uint32_t field : fields) {
        if (heuristics.divisible_by > 1) {
            if (field % heuristics.divisible_by != 0) {
                continue;
            }
        }

        if (field <= heuristics.greater_than_value) {
            continue;
        }

        if (heuristics.size_divisor > 0) {
            const size_t min_bound = m_metadata.size() / heuristics.size_divisor;
            if (field <= min_bound) {
                continue;
            }
        }

        if (heuristics.require_in_bounds) {
            if (field > m_metadata.size()) {
                continue;
            }
        }

        probable_offsets.push_back(field);
    }

    return probable_offsets;
}