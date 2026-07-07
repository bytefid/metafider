#ifndef METAFIDER_METAFIDERAPP_H
#define METAFIDER_METAFIDERAPP_H

#include <optional>

#include "config/ConfigLoader.h"
#include "io_manager/IOManager.h"
#include "heuristics/Heuristics.h"
#include "metadata_parser/MetadataParser.h"

class MetafiderApp {
public:
    bool Init(const metafider::config::AppConfig &config);
    bool Load();
    bool Parse();

    void PrintData() const;

private:
    metafider::config::AppConfig config = {};
    IOManager io_manager;
    Heuristics heuristics;
    std::shared_ptr<std::vector<uint8_t>> metadata;
    std::optional<MetadataParser> metadata_parser;
};



#endif //METAFIDER_METAFIDERAPP_H
