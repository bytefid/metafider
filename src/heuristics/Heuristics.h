#ifndef METAFIDER_HEURISTICS_H
#define METAFIDER_HEURISTICS_H

#include <vector>
#include <cstdint>
#include <cstddef>

namespace HConfig {
    struct OffsetHeuristics {
        uint32_t greater_than_value = 8192;
        uint32_t divisible_by = 4;
        uint32_t size_divisor = 8;
        bool require_in_bounds = true;
    };
}

class Heuristics {
private:
    HConfig::OffsetHeuristics m_offset_heuristics = {};

public:
    Heuristics() = default;

    void SetOffsetHeuristics(const HConfig::OffsetHeuristics& OffsetHeuristics);

    bool IsProbableOffset(
        const std::vector<uint8_t>& metadata,
        uint32_t field
    );
};

#endif //METAFIDER_HEURISTICS_H
