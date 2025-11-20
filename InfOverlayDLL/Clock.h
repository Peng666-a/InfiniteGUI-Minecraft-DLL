#pragma once
#include "Module.h"
#include "AffixModule.h"
#include "WindowModule.h"
#include "UpdateModule.h"
#include <string>

class Clock : public Module, public AffixModule , public WindowModule, public UpdateModule {
public:
    Clock() {
        type = ModuleType::Singleton;
        name = u8"时钟";
        description = u8"显示现在的系统时间";
        currentTimeStr = u8"时间获取中...";
    }

    const char* GetTypeName() const override { return "Clock"; }

    void Update() override;
    void DrawContent() override;
    void DrawSettings() override;
    void Load(const nlohmann::json& j) override;
    void Save(nlohmann::json& j) const override;

private:
    std::string currentTimeStr;
};