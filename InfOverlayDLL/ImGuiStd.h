#pragma once
#include "imgui/imgui.h"
#include <string>

namespace ImGuiStd {

    static bool InputTextStd(const char* label, std::string& str, ImGuiInputTextFlags flags = 0)
    {
        char buffer[1024];
        strncpy(buffer, str.c_str(), sizeof(buffer));
        buffer[sizeof(buffer) - 1] = 0;

        if (ImGui::InputText(label, buffer, sizeof(buffer), flags)) {
            str = buffer;
            return true;
        }
        return false;
    }

    static void TextShadow(const char* text, ImVec4 shadowColor, ImVec2 offset, ...)
    {
        ImVec2 pos = ImGui::GetCursorPos();
        ImGui::SetCursorPos(ImVec2(pos.x + offset.x, pos.y + offset.y));
        ImGui::TextColored(shadowColor, text);  // 阴影层

        ImGui::SetCursorPos(pos);
        ImGui::Text(text);  // 正常文字
    }

    static void TextShadow(const char* text, ...)
    {
        ImVec2 pos = ImGui::GetCursorPos();
        ImGui::SetCursorPos(ImVec2(pos.x + 1, pos.y + 1));
        ImGui::TextColored(ImVec4(0, 0, 0, 0.6f), text);  // 阴影层

        ImGui::SetCursorPos(pos);
        ImGui::Text(text);  // 正常文字
    }

    static void TextColoredShadow(ImVec4 color, ImVec4 shadowColor, const char* text, ImVec2 offset, ...)
    {
        ImVec2 pos = ImGui::GetCursorPos();
        ImGui::SetCursorPos(ImVec2(pos.x + offset.x, pos.y + offset.y));
        ImGui::TextColored(shadowColor, text);  // 阴影层

        ImGui::SetCursorPos(pos);
        ImGui::TextColored(color, text);  // 正常文字
    }

    static void TextColoredShadow(ImVec4 color, const char* text, ...)
    {
        ImVec2 pos = ImGui::GetCursorPos();
        ImGui::SetCursorPos(ImVec2(pos.x + 1, pos.y + 1));
        ImGui::TextColored(ImVec4(0, 0, 0, 0.6f), text);  // 阴影层

        ImGui::SetCursorPos(pos);
        ImGui::TextColored(color, text);  // 正常文字
    }

}
