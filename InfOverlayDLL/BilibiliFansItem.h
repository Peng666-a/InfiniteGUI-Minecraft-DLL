#pragma once
#include "InfoItem.h"
#include <string>


struct bilibili_fans_element {
    ImVec4 color;
};

class BilibiliFansItem : public InfoItem {
public:
    BilibiliFansItem() {
        windowTitle = "Bilibili Fans";
        refreshIntervalMs = 30000;   // 默认 30 秒刷一次
    }

    void Update() override;
    void DrawContent() override;
    void Load(const nlohmann::json& j) override;
    void Save(nlohmann::json& j) const override;

public:
    long long uid = 399194206;          // B站用户UID
    int fansCount = 0;    // 粉丝数（从API解析）
    int lastFansCount = 0;    // 粉丝数（从API解析）
    bilibili_fans_element color = { ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_Text)) };
};