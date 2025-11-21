#pragma once
#include "Item.h"
#include "AffixModule.h"
#include "WindowModule.h"
#include "UpdateModule.h"
#include "SoundModule.h"
#include <string>

struct counter_element {
    ImVec4 color;
};

class CounterItem : public Item, public AffixModule, public WindowModule, public UpdateModule, public SoundModule
{
public:
    CounterItem() {
        type = Hud; // 信息项类型
        multiType = MultiInstance;    // 信息项是否可以多开
        name = u8"计数器";
        description = u8"显示计数器";
        isPlaySound = true;
        soundVolume = 0.5f;
        refreshIntervalMs = 50;
        lastUpdateTime = std::chrono::steady_clock::now();
    }
    ~CounterItem() {}

    void Update() override;
    void DrawContent() override;
    void DrawSettings() override;
    void Load(const nlohmann::json& j) override;
    void Save(nlohmann::json& j) const override;

    int count = 0;
    int lastCount = 0;
    float fontSize = 20.0f;


    int hotkeyAdd = VK_F6;   // 默认快捷键
    int hotkeySub = VK_F5;

    counter_element color = { ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_Text)) };
};