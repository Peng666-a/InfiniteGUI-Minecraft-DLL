#include "GlobalConfig.h"
#include "ConfigManager.h"
void GlobalConfig::Load(const nlohmann::json& j)
{
    if (j.contains("fontPath")) fontPath = j["fontPath"];
    if (j.contains("currentProfile")) currentProfile = j["currentProfile"];
}

void GlobalConfig::Save(nlohmann::json& j) const
{
    j["fontPath"] = fontPath;
    j["currentProfile"] = currentProfile;
}