#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <windows.h>
#include "Module.h"
#include "ModuleFactory.h"

class ModuleManager
{
public:
    ModuleManager() = default;
    ~ModuleManager();

    // 添加模块
    void AddModule(std::shared_ptr<Module> module);

    // 删除模块（仅多实例）
    void RemoveModule(std::shared_ptr<Module> module);

    // 获取单例模块（通过类型名）
    std::shared_ptr<Module> GetSingleton(const std::string& typeName);

    // 创建模块实例（外部 UI 会用到）
    std::shared_ptr<Module> CreateModule(const std::string& typeName);

    // 更新所有模块
    void UpdateAll();

    // 渲染所有窗口模块
    void RenderAll(HWND hwnd);

    // 绘制所有模块的设置 UI
    void DrawAllSettings();

    // 保存所有模块配置
    void SaveConfig(nlohmann::json& j) const;

    // 加载所有模块配置（会自动创建多实例）
    void LoadConfig(const nlohmann::json& j);

    // 获取模块列表
    const std::vector<std::shared_ptr<Module>>& GetModules() const { return allModules; }

private:
    // 所有模块（包括单例 + 多实例）
    std::vector<std::shared_ptr<Module>> allModules;

    // 单例模块
    std::unordered_map<std::string, std::shared_ptr<Module>> singletonModules;

    // 多实例模块
    std::vector<std::shared_ptr<Module>> multiModules;
};
