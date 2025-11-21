#include "FpsItem.h"
#include "ImGuiStd.h"


void FpsItem::Update()
{
	FPS = float(frameCount) / (float(refreshIntervalMs) / 1000.0f);
	frameCount = 0;
}
void FpsItem::DrawContent()
{
	frameCount++;
	int FPS = int(this->FPS);
	ImGuiStd::TextShadow((prefix + std::to_string(FPS) + suffix).c_str());
}

void FpsItem::DrawSettings()
{
	DrawModuleSettings();
	ImGui::Text(u8"FPS 无额外设置");
	if (ImGui::CollapsingHeader(u8"通用设置"))
	{
		DrawWindowSettings();
		DrawAffixSettings();
	}
}

void FpsItem::Load(const nlohmann::json& j)
{
	LoadItem(j);
	LoadAffix(j);
	LoadWindow(j);
}
void FpsItem::Save(nlohmann::json& j) const
{
	SaveItem(j);
	SaveAffix(j);
	SaveWindow(j);
}