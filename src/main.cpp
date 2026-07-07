#include <print>

#include "config/ConfigLoader.h"
#include "metafider_app/MetafiderApp.h"

int main() {
    const auto config_result = metafider::config::LoadConfig("config.json");
    if (!config_result.has_value()) {
        std::print("Failed to load config: {}\n", IO::ToCString(config_result.error()));
        return 1;
    }
    const auto& app_config = config_result.value();

    MetafiderApp main_app;
    if (!main_app.Init(app_config)) {
        return 1;
    }

    if (!main_app.Load()) {
        return 1;
    }

    main_app.Parse();

    return 0;
}