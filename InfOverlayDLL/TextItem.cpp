#include "TextItem.h"
#include "ImGuiStd.h"

void TextItem::Update(){}

void TextItem::DrawContent()
{
    ImGuiStd::TextShadow((prefix + text + suffix).c_str());
    //ImGui::Text((prefix + text + suffix).c_str());
}

void TextItem::Load(const nlohmann::json& j)
{
    if (j.contains("text")) text = j["text"];
    LoadInfoItemConfig(j);
}

void TextItem::Save(nlohmann::json& j) const
{
    j["type"] = "text";
    j["text"] = text;
    SaveInfoItemConfig(j);
}