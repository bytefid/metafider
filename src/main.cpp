#include <print>

#include "config/ConfigLoader.h"
#include "metafider_app/MetafiderApp.h"

int main() {
    const auto config_result = metafider::config::LoadConfig("config.json");
    if (!config_result.has_value()) {
        std::print("Failed to load config: {}\n", IO::ToCString(config_result.error()));
        return 1;
    }
    const auto& config = config_result.value();

    MetafiderApp main_app;
    if (!main_app.Init(config.offset_heuristics)) {
        return 1;
    }

    if (!main_app.Load(config.metadata_path)) {
        return 1;
    }

    main_app.Parse(config.header_size);
    main_app.PrintData();

    return 0;
}