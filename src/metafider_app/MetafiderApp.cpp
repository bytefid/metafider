#include "MetafiderApp.h"

#include <print>
#include "metadata_parser/MetadataParser.h"


bool MetafiderApp::Init() {
    io_manager = IOManager();
    heuristics = Heuristics();
    heuristics.SetOffsetHeuristics({
        .greater_than_value = 0,
        .divisible_by = 2,
        .size_divisor = 32,
        .require_in_bounds = true
    });
    return true;
}

bool MetafiderApp::Load(const std::string &metadata_path) {
    const auto metadata_result = io_manager.LoadMetadata(metadata_path);
    if (!metadata_result.has_value()) {
        std::print("Init error: {}\n", IO::ToCString(metadata_result.error()));
        return false;
    }
    metadata = std::make_shared<std::vector<uint8_t>>(metadata_result.value());
    metadata_parser.emplace(io_manager, heuristics, metadata);
    return true;
}

bool MetafiderApp::Parse() {
    if (const auto fields_result = metadata_parser.value().ParseFields(380); !fields_result.has_value()) {
        std::print("Parse error: {}\n", IO::ToCString(fields_result.error()));
        return false;
    }

    const MetadataParsed::data data = metadata_parser.value().GetParsedData();

    if (const auto offsets_result = metadata_parser.value().ParseOffsets(data.fields); !offsets_result.has_value()) {
        std::print("Parse error: {}\n", IO::ToCString(offsets_result.error()));
        return false;
    }
    return true;
}

void MetafiderApp::PrintData() const {
    MetadataParsed::data data = metadata_parser.value().GetParsedData();
    const auto& fields = data.fields;
    const auto& offsets = data.offsets;

    std::print("Parsed {} fields successfully.\n", fields.size());

    std::print("Found {} probable offsets.\n", offsets.size());
    for (size_t i = 0; i < offsets.size(); ++i) {
        std::print("[{}]: {:#010x}\n", i+1, offsets[i]);
    }
}

