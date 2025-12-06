#include "GlobalConfig.h"

void GlobalConfig::Load(const nlohmann::json& j)
{
    if (j.contains("fontPath")) fontPath = j["fontPath"];
}

void GlobalConfig::Save(nlohmann::json& j) const
{
    j["fontPath"] = fontPath;
}