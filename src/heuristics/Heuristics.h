#ifndef METAFIDER_HEURISTICS_H
#define METAFIDER_HEURISTICS_H

#include <vector>
#include <cstdint>
#include <cstddef>

namespace HProperties {
    struct OffsetHeuristics {
        uint32_t greater_than_value;
        uint32_t divisible_by;
        uint32_t size_divisor;
        bool require_in_bounds;
    };
}

class Heuristics {
public:
    Heuristics() = default;

    void SetOffsetHeuristics(const HProperties::OffsetHeuristics& OffsetHeuristics);

    bool IsProbableOffset(
        const std::vector<uint8_t>& metadata,
        uint32_t field
    ) const;

private:
    HProperties::OffsetHeuristics m_offset_heuristics = {};
};

#endif //METAFIDER_HEURISTICS_H
