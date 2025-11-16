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
void FpsItem::Load(const nlohmann::json& j)
{
	LoadInfoItemConfig(j);
}
void FpsItem::Save(nlohmann::json& j) const
{
	j["type"] = "fps";
	SaveInfoItemConfig(j);
}