#include "ConfigLoader.h"

#include <fstream>
#include <nlohmann/json.hpp>

namespace metafider::config {

    std::expected<AppConfig, IO::Error> LoadConfig(const std::string& config_path) {
        std::ifstream file(config_path);
        if (!file.is_open()) {
            return std::unexpected(IO::Error::OpenError);
        }

        nlohmann::json json_data;
        try {
            file >> json_data;
        } catch (const nlohmann::json::parse_error&) {
            return std::unexpected(IO::Error::ReadError);
        }

        try {
            AppConfig config;
            config.header_size = json_data.at("header_size").get<size_t>();
            config.metadata_path = json_data.at("metadata_path").get<std::string>();

            const auto& h = json_data.at("offset_heuristics");
            config.offset_heuristics = HProperties::OffsetHeuristics{
                .greater_than_value = h.at("greater_than_value").get<uint32_t>(),
                .divisible_by = h.at("divisible_by").get<uint32_t>(),
                .size_divisor = h.at("size_divisor").get<uint32_t>(),
                .require_in_bounds = h.at("require_in_bounds").get<bool>()
            };
            return config;
        } catch (const nlohmann::json::out_of_range&) {
            return std::unexpected(IO::Error::ReadError);
        }
    }

}