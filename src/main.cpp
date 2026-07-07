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

    Heuristics heuristics;
    heuristics.SetOffsetHeuristics(
        {0, 2, 32, true}
        );

    MetadataParser parser(io_manager, heuristics, metadata);

    const auto fields_result = parser.ParseFields(380);
    if (!fields_result.has_value()) {
        return 1;
    }
    const auto& fields = fields_result.value();
    std::print("Parsed {} fields successfully.\n", fields.size());


    const auto offsets_result = parser.ParseOffsets(fields);
    if (!offsets_result.has_value()) {
        return 1;
    }

    const auto& offsets = offsets_result.value();
    std::print("Found {} probable offsets.\n", offsets.size());
    for (size_t i = 0; i < offsets.size(); ++i) {
        std::print("[{}]: {:#010x}\n", i+1, offsets[i]);
    }

    return 0;
}