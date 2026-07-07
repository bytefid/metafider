#ifndef METAFIDER_METAFIDERAPP_H
#define METAFIDER_METAFIDERAPP_H

#include <optional>

#include "io_manager/IOManager.h"
#include "heuristics/Heuristics.h"
#include "metadata_parser/MetadataParser.h"

class MetafiderApp {
public:
    bool Init();
    bool Load(const std::string &metadata_path);
    bool Parse();

    void PrintData() const;

    bool Init(HProperties::OffsetHeuristics offset_heuristics);

    bool Parse(size_t header_size);

private:
    IOManager io_manager;
    Heuristics heuristics;
    std::shared_ptr<std::vector<uint8_t>> metadata;
    std::optional<MetadataParser> metadata_parser;
};



#endif //METAFIDER_METAFIDERAPP_H
