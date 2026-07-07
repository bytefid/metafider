#include <print>
#include "metadata_parser/MetadataParser.h"

int main() {
    std::print("Hello World!\n");
    IOManager io_manager;
    const auto metadata_result = io_manager.LoadMetadata("meta_raw.dat");
    if (!metadata_result.has_value()) {
        return 1;
    }
    const auto& metadata = metadata_result.value();

    MetadataParser parser(io_manager, metadata);

    const auto fields_result = parser.ParseFields(380);
    if (!fields_result.has_value()) {
        return 1;
    }

    const auto& fields = fields_result.value();
    std::print("Parsed {} fields successfully.\n", fields.size());

    constexpr OffsetHeuristics heuristics{};

    const auto offsets_result = parser.ParseOffsets(fields, heuristics);
    if (!offsets_result.has_value()) {
        return 1;
    }

    const auto& offsets = offsets_result.value();
    std::print("Found {} probable offsets.\n", offsets.size());

    return 0;
}