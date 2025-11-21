#pragma once
#include <string>
#include "GlobalConfig.h"
#include "ItemManager.h"

class ConfigManager {
public:
    static bool Save(const std::string& filePath,
        const GlobalConfig& global,
        const ItemManager& info);

    static bool Load(const std::string& filePath,
        GlobalConfig& global,
        ItemManager& info);
};