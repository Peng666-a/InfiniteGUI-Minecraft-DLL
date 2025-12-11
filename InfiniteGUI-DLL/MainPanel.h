#pragma once

enum PanelType
{
	ModulePanel,
	SettingsPanel,
	MorePanel,
	AboutPanel,
};

constexpr ImVec2 mainPanelSize = ImVec2(900.0f - 190.0f, 556.0f);
constexpr float padding = 20.0f;
class MainPanel
{
public:
	void Draw()
	{
		ImVec2 screenPos = ImGui::GetCursorScreenPos();

		ImDrawList* draw = ImGui::GetWindowDrawList();

		ImVec2 pos1 = ImVec2(screenPos.x + padding * 0.5f, screenPos.y + 60);
		ImVec2 pos2 = ImVec2(screenPos.x + mainPanelSize.x - padding * 0.5f, screenPos.y + 60);

		draw->AddLine(pos1, pos2, ImGui::GetColorU32(ImGuiCol_Separator), 1.0f);

		ImGui::SetCursorPos(ImVec2(screenPos.x + padding, screenPos.y + 60 + padding));
		ImGui::Dummy(ImVec2(150.0f, 0.0f));
		switch (m_panelType)
		{
		case ModulePanel:
			// Draw Module Panel
			break;
		case SettingsPanel:
			// Draw Settings Panel
			break;
		case MorePanel:
			// Draw More Panel
			break;
		case AboutPanel:
			// Draw About Panel
			break;
		}
	}

	void SetPanelType(PanelType type) { m_panelType = type; }
	PanelType GetPanelType() const { return m_panelType; }

private:
	PanelType m_panelType;
};
