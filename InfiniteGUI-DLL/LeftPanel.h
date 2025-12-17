#pragma once
#include "SelectPanel.h"
#include "ImGuiStd.h"
#include "opengl_hook.h"
constexpr ImVec2 headerLogoPos = ImVec2(45.0f, 6.0f);
constexpr ImVec2 heaaderLogoSize = ImVec2(100.0f, 100.0f);



class LeftPanel
{
public:
	LeftPanel()
	{
		selectedPanel = new SelectPanel();
	}
	~LeftPanel()
	{
		delete selectedPanel;
	}
	void Draw()
	{
		DrawHeader();
		ImGui::SetCursorPos(ImVec2(20.0f, 115.0f));
		ImGui::PushFont(NULL, ImGui::GetFontSize() * 1.20f);
		selectedIndex = selectedPanel->Draw();
		ImGui::PopFont();
	}
	int GetSelectedIndex() const { return selectedIndex; }
private:

	SelectPanel* selectedPanel;
	int selectedIndex = 0;
	void DrawHeader()
	{
		// 居中绘制图片
		ImGui::SetCursorPos(headerLogoPos);
		ImGui::Image(opengl_hook::gui.logoTexture.id,
			heaaderLogoSize
		);
	}
};
