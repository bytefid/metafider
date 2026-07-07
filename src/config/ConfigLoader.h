#ifndef METAFIDER_CONFIGLOADER_H
#define METAFIDER_CONFIGLOADER_H

#include <string>
#include <expected>

#include "heuristics/Heuristics.h"
#include "io_manager/IOManager.h"

namespace metafider::config {

    struct AppConfig {
        size_t header_size;
        HProperties::OffsetHeuristics offset_heuristics;
        std::string metadata_path;
    };

    std::expected<AppConfig, IO::Error> LoadConfig(const std::string& config_path);

} // namespace metafider::config

#endif //METAFIDER_CONFIGLOADER_H
