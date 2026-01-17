#pragma once

#include <filesystem>
#include <string>
#include <vector>

void Finish(int);

typedef struct EntryInfo {
    std::vector<std::string> Files;
    std::vector<std::string> ExtrasArguments;
} EntryInfo;

extern void PassControl(EntryInfo);