#pragma once
#include "LeftPanel.h"
#include "MainPanel.h"

constexpr ImVec2 settingMenuSize = ImVec2(900, 556);
class SettingMenu
{
public:
	SettingMenu()
	{
		leftPanel = new LeftPanel();
		mainPanel = new MainPanel();
		exitButton = new MyButton("9", ImVec2(30.0f, 30.0f));
	}
	~SettingMenu()
	{
		delete leftPanel;
		delete mainPanel;
		delete exitButton;
	}
	void Init() const
	{
		mainPanel->Init();
	}
	bool Draw() const
	{

		ImGui::BeginChild(u8"主控制面板Inner", settingMenuSize, true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		//将退出按钮显示在右上角
		ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 30 - 15.0f, 15.0f));
		bool exit = false;
		ImGui::PushFont(opengl_hook::gui.iconFont);
		if (exitButton->Draw())
		{
			exit = true;
		}
		ImGui::PopFont();
		ImGui::SetCursorPos(ImVec2(0.0f, 0.0f));
		ImVec2 screenPos = ImGui::GetCursorScreenPos();

		ImDrawList* draw = ImGui::GetWindowDrawList();
		ImVec2 LeftPanelBg1 = ImVec2(0.0f, 0.0f);
		ImVec2 LeftPanelBg2 = ImVec2(padding * 2 + 150.0f + screenPos.x, settingMenuSize.y + screenPos.y);
		//ImVec4 LeftPanelBgColor = ImGui::GetColorU32(ImGuiCol_ChildBg)
		draw->AddRectFilled(LeftPanelBg1, LeftPanelBg2, ImGui::GetColorU32(ImGuiCol_WindowBg));



		leftPanel->Draw();
		int index = leftPanel->GetSelectedIndex();
		ImVec2 pos1 = ImVec2(padding * 2 + 150.0f + screenPos.x, screenPos.y);
		ImVec2 pos2 = ImVec2(padding * 2 + 150.0f + screenPos.x, settingMenuSize.y + screenPos.y);
		draw->AddLine(pos1, pos2, ImGui::GetColorU32(ImGuiCol_Separator), 1.0f);
		ImGui::SetCursorPos(ImVec2(padding * 2 + 150.0f, 0.0f));
		mainPanel->SetPanelType(index);
		mainPanel->Draw();
		ImGui::EndChild();
		return exit;
	}

private:
	LeftPanel * leftPanel;
	MainPanel * mainPanel;
	MyButton * exitButton;
};
