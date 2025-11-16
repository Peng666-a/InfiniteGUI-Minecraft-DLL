#pragma once
#include "InfoItem.h"
#include <string>
#include <chrono>
#include <ctime>

class TimeItem : public InfoItem {
public:
    TimeItem() {
        windowTitle = "Time";
        refreshIntervalMs = 1000;  // Ä¬ÈÏ1ÃëË¢ÐÂ
    }

    void Update() override;
    void DrawContent() override;
    void Load(const nlohmann::json& j) override;
    void Save(nlohmann::json& j) const override;

private:
    std::string currentTimeStr;
};