#include "Clock.h"
#include <iomanip>
#include <sstream>
#include "ImGuiStd.h"
#include "ModuleFactory.h"

static bool clock_registered = []() {
    ModuleFactory::Instance().RegisterType("Clock", []() {
        return std::make_shared<Clock>();
        });
    return true;
    }();

void Clock::Update()
{
    // 获取系统当前时间
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};
#ifdef _WIN32
    localtime_s(&localTime, &t);
#else
    localtime_r(&t, &localTime);
#endif

    // 转换成字符串
    std::stringstream ss;
    ss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

    currentTimeStr = ss.str();
}

void Clock::DrawContent()
{
    ImGuiStd::TextShadow((prefix + currentTimeStr + suffix).c_str());
}

void Clock::DrawSettings()
{
    DrawModuleSettings();
    ImGui::Text(u8"时钟 无额外设置");
    if (ImGui::CollapsingHeader(u8"通用设置"))
    {
        DrawUpdateSettings();
        DrawWindowSettings();
        DrawAffixSettings();
    }

}

void Clock::Load(const nlohmann::json& j)
{
    LoadModuleConfig(j);
    LoadUpdateConfig(j);
    LoadWindowConfig(j);
    LoadAffixConfig(j);
}

void Clock::Save(nlohmann::json& j) const
{
    j["type"] = name;
    SaveModuleConfig(j);
    SaveUpdateConfig(j);
    SaveWindowConfig(j);
    SaveAffixConfig(j);
}