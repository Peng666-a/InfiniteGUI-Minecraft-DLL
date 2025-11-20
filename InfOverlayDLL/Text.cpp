#include "Text.h"
#include "ImGuiStd.h"
#include "ModuleFactory.h"

static bool text_registered = []() {
    ModuleFactory::Instance().RegisterType("Text", []() {
        return std::make_shared<Text>();
        });
    return true;
    }();

void Text::DrawContent()
{
    ImGuiStd::TextShadow((prefix + text + suffix).c_str());
}

void Text::DrawSettings()
{
    DrawModuleSettings();
    ImGuiStd::InputTextStd(u8"文本内容", text);
    if (ImGui::CollapsingHeader(u8"通用设置"))
    {
        DrawWindowSettings();
        DrawAffixSettings();
    }
}

void Text::Load(const nlohmann::json& j)
{
    LoadModuleConfig(j);
    LoadWindowConfig(j);
    LoadAffixConfig(j);
    if (j.contains("text")) text = j["text"];
}

void Text::Save(nlohmann::json& j) const
{
    j["type"] = name;
    SaveModuleConfig(j);
    SaveWindowConfig(j);
    SaveAffixConfig(j);
    j["text"] = text;
}