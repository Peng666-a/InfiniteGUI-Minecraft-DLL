#pragma once
#include <string>
#include "GlobalConfig.h"
#include "InfoManager.h"

class ConfigManager {
public:

    static std::string GetRunPath();

    static std::string GetConfigPath();

    static bool Save(const std::string& filePath,
        const GlobalConfig& global,
        const InfoManager& info);

    static bool Load(const std::string& filePath,
        GlobalConfig& global,
        InfoManager& info);
};