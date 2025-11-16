#include "TimeItem.h"
#include <iomanip>
#include <sstream>
#include "ImGuiStd.h"

void TimeItem::Update()
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

void TimeItem::DrawContent()
{
    ImGuiStd::TextShadow((prefix + currentTimeStr + suffix).c_str());
}

void TimeItem::Load(const nlohmann::json& j)
{
    LoadInfoItemConfig(j);
}

void TimeItem::Save(nlohmann::json& j) const
{
    j["type"] = "time";
    SaveInfoItemConfig(j);
}