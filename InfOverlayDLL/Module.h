#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "imgui\imgui.h"
enum class ModuleType {
    Singleton,   // 每种模块只有一个实例
    MultiInstance // 可以创建多个实例
};

class Module {
public:

    virtual const char* GetTypeName() const = 0;

    virtual void Load(const nlohmann::json& j) = 0;
    virtual void Save(nlohmann::json& j) const = 0;
    virtual void DrawSettings() = 0;

    void DrawModuleSettings()
    {
        ImGui::Checkbox(u8"启用", &isEnabled);
    }

    void LoadModuleConfig(const nlohmann::json& j) {
        if(j.contains("isEnabled")) isEnabled = j.value("isEnabled", true);
    }

    void SaveModuleConfig(nlohmann::json& j) const {
        j["isEnabled"] = isEnabled;
    }

    ModuleType type = ModuleType::Singleton;

    bool isEnabled = false;           // 是否启用模块
    //int ID = 0;                     // 模块 ID
    std::string name = "Module";    // 模块名称
    std::string description = "";   // 模块描述
};