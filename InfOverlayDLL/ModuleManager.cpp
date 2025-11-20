#include "ModuleManager.h"
#include "WindowModule.h"
#include "UpdateModule.h"
#include "ImGuiStd.h"

ModuleManager::~ModuleManager()
{
    allModules.clear();
    singletonModules.clear();
    multiModules.clear();
}

// 添加模块
void ModuleManager::AddModule(std::shared_ptr<Module> module)
{
    allModules.push_back(module);

    if (module->type == ModuleType::Singleton)
    {
        singletonModules[module->GetTypeName()] = module;
    }
    else
    {
        multiModules.push_back(module);
    }
}

// 删除模块（仅多实例）
void ModuleManager::RemoveModule(std::shared_ptr<Module> module)
{
    if (module->type == ModuleType::Singleton)
        return; // 单例不允许删除

    // 从 allModules 删除
    allModules.erase(std::remove(allModules.begin(), allModules.end(), module), allModules.end());

    // 从多实例列表删除
    multiModules.erase(std::remove(multiModules.begin(), multiModules.end(), module), multiModules.end());
}

std::shared_ptr<Module> ModuleManager::GetSingleton(const std::string& typeName)
{
    auto it = singletonModules.find(typeName);
    return (it != singletonModules.end()) ? it->second : nullptr;
}

// 创建新模块实例（用于 UI 的 “添加模块”）
std::shared_ptr<Module> ModuleManager::CreateModule(const std::string& typeName)
{
    auto mod = ModuleFactory::Instance().Create(typeName);
    if (mod)
        AddModule(mod);
    return mod;
}

// 更新所有模块
void ModuleManager::UpdateAll()
{
    for (auto& m : allModules)
    {
        if (auto upd = dynamic_cast<UpdateModule*>(m.get()))
        {
            if (upd->ShouldUpdate())
                upd->Update();
        }
    }
}

// 渲染所有窗口模块
void ModuleManager::RenderAll(HWND hwnd)
{
    for (auto& m : allModules)
    {
        if (m->isEnabled) continue; // 跳过禁用的模块
        if (auto win = dynamic_cast<WindowModule*>(m.get()))
        {
                win->RenderWindow(nullptr, hwnd);
        }
    }
}

// 绘制所有模块设置
void ModuleManager::DrawAllSettings()
{
    for (auto& m : allModules)
    {
        if (!m->isEnabled)
            continue;

        std::string id = m->name + "##" + std::to_string((uintptr_t)m.get());

        if (ImGui::CollapsingHeader(id.c_str()))
        {
            m->DrawSettings();

            // 允许删除多实例模块
            if (m->type == ModuleType::MultiInstance)
            {
                if (ImGui::Button(("删除此模块##" + id).c_str()))
                {
                    RemoveModule(m);
                    break;
                }
            }
        }
    }
}

// 保存所有配置
void ModuleManager::SaveConfig(nlohmann::json& j) const
{
    j = nlohmann::json::object();
    j["singleton"] = nlohmann::json::object();
    j["multi"] = nlohmann::json::array();

    // 单例
    for (auto& p : singletonModules)
    {
        auto& mod = p.second;
        nlohmann::json mj;
        mod->Save(mj);
        j["singleton"][mod->GetTypeName()] = mj;
    }

    // 多实例
    for (auto& mod : multiModules)
    {
        nlohmann::json mj;
        mj["type"] = mod->GetTypeName();
        mod->Save(mj);
        j["multi"].push_back(mj);
    }
}

// 加载所有配置（会自动创建多实例模块）
void ModuleManager::LoadConfig(const nlohmann::json& j)
{
    // 单例模块恢复
    if (j.contains("singleton"))
    {
        for (auto it = j["singleton"].begin(); it != j["singleton"].end(); ++it)
        {
            std::string typeName = it.key();
            auto mod = GetSingleton(typeName);
            if (mod)
                mod->Load(it.value());
        }
    }

    // 多实例模块恢复
    if (j.contains("multi"))
    {
        for (auto& item : j["multi"])
        {
            if (!item.contains("type"))
                continue;

            std::string typeName = item["type"];

            // 工厂创建实例
            auto mod = ModuleFactory::Instance().Create(typeName);
            if (!mod)
                continue;

            // 载入配置
            mod->Load(item);

            // 加入系统
            AddModule(mod);
        }
    }
}
