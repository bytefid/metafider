#include "Heuristics.h"

void Heuristics::SetOffsetHeuristics(const HConfig::OffsetHeuristics &OffsetHeuristics) {
    m_offset_heuristics = OffsetHeuristics;
}

bool Heuristics::IsProbableOffset(
        const std::vector<uint8_t>& metadata,
        const uint32_t field
    ) {
    if (m_offset_heuristics.divisible_by > 1) {
        if (field % m_offset_heuristics.divisible_by != 0) {
            return false;
        }
    }

    if (field <= m_offset_heuristics.greater_than_value) {
        return false;
    }

    if (m_offset_heuristics.size_divisor > 0) {
        if (const size_t min_bound = metadata.size() / m_offset_heuristics.size_divisor; field <= min_bound) {
            return false;
        }
    }

    if (m_offset_heuristics.require_in_bounds) {
        if (field > metadata.size()) {
            return false;
        }
    }

    return true;
}
