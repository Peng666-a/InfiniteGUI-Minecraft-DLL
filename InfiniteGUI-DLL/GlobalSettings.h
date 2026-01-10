#pragma once
#include "ConfigSelector.h"
#include "FontSelector.h"
#include "menuRule.h"
#include "ItemManager.h"
class GlobalSettings
{
public:
	GlobalSettings()
	{
		m_configSelector = new ConfigSelector();
		m_fontSelector = new FontSelector();
	}
	~GlobalSettings()
	{
		delete m_configSelector;
		delete m_fontSelector;
	}
	void Draw() const
	{
		bool exit = false;
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings;
		//ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(12.0f, 8.0f));
		ImGui::BeginChild("GlobalSettings", ImVec2(-padding + ImGui::GetStyle().WindowPadding.x, -padding + ImGui::GetStyle().WindowPadding.y), true, flags);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12.0f, 8.0f));

		// ===== 布局参数 =====
		ImGuiStyle& style = ImGui::GetStyle();
		float basePadding = style.WindowPadding.x;
		float bigPadding = basePadding * 3.0f;

		// 获取窗口可用宽度
		float contentWidth = ImGui::GetContentRegionAvail().x;
		float centerX = contentWidth * 0.5f;

		// 每个输入框宽度（留点余量，避免顶到边）
		float itemWidth = centerX - bigPadding * 4.0f;

		float startY = ImGui::GetCursorPosY();

		ImGui::PushFont(NULL, ImGui::GetFontSize() * 0.8f);
		ImGui::BeginDisabled();
		ImGuiStd::TextShadow(u8"配置选择：");
		ImGui::EndDisabled();
		ImGui::PopFont();

		ImGui::SetCursorPosX(bigPadding);
		ImGui::BeginChild("ConfigSelector", ImVec2(centerX - bigPadding, 192.0f), true, ImGuiWindowFlags_NoScrollbar);
		m_configSelector->Draw();
		ImGui::EndChild();

		ImGui::SetCursorPos(ImVec2(centerX + basePadding, startY));

		ImGui::PushFont(NULL, ImGui::GetFontSize() * 0.8f);
		ImGui::BeginDisabled();
		ImGuiStd::TextShadow(u8"字体选择：");
		ImGui::EndDisabled();
		ImGui::PopFont();

		ImGui::SetCursorPosX(bigPadding + centerX);
		ImGui::BeginChild("FontSelector", ImVec2(centerX - bigPadding, 192.0f), true, ImGuiWindowFlags_NoScrollbar);
		m_fontSelector->Draw();
		ImGui::EndChild();

		//ImGui::SetCursorPosX(0.0f);
		for(auto& item : ItemManager::Instance().GetItems())
		{
			if(item->type == Hidden)
				item->DrawSettings(bigPadding, centerX, itemWidth);
		}

		ImGui::PopStyleVar();
		ImGui::EndChild();
	}
private:
	ConfigSelector *m_configSelector;
	FontSelector *m_fontSelector;
};
