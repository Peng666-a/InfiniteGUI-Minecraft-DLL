#pragma once
#include <vector>

#include "FileUtils.h"
#include "fonts.h"
#include "GlobalConfig.h"
#include "opengl_hook.h"
#include "imgui/imgui.h"

struct FontInfo {
    std::string name;
    std::wstring path;
};

class FontSelector
{
public:
    void Draw() {
        ImGuiIO& io = ImGui::GetIO();
        // Get font files if not loaded yet
        if (fontFiles.empty()) {
            fontFiles = GetFontsFromDirectory(L"C:\\Windows\\Fonts");

            // 获取用户名
            wchar_t username[256]; // 确保足够空间来存储用户名
            DWORD usernameSize = sizeof(username) / sizeof(username[0]);
            GetUserNameW(username, &usernameSize);
            std::vector<FontInfo> userFonts = GetFontsFromDirectory(L"C:\\Users\\" + std::wstring(username) + L"\\AppData\\Local\\Microsoft\\Windows\\Fonts");
            fontFiles.insert(fontFiles.end(), userFonts.begin(), userFonts.end());
        }

        ImFontConfig font_cfg;
        font_cfg.FontDataOwnedByAtlas = false;
        font_cfg.OversampleH = 1;
        font_cfg.OversampleV = 1;
        font_cfg.PixelSnapH = true;

        if (ImGui::Selectable(u8"默认字体-阿里巴巴普惠体")) {
            // Load the selected font
            opengl_hook::gui.font = io.Fonts->AddFontFromMemoryTTF(Fonts::alibaba.data, Fonts::alibaba.size, 20.0f, &font_cfg, io.Fonts->GetGlyphRangesChineseFull());
            io.FontDefault = opengl_hook::gui.font;
            GlobalConfig::Instance().fontPath = "default";
        }

        for (size_t i = 0; i < fontFiles.size(); ++i) {
            if (ImGui::Selectable(fontFiles[i].name.c_str())) {
                // Load the selected font
                opengl_hook::gui.font = io.Fonts->AddFontFromFileTTF(StringConverter::WstringToUtf8(fontFiles[i].path).c_str(), 20.0f, &font_cfg, ImGui::GetIO().Fonts->GetGlyphRangesChineseFull());
                io.FontDefault = opengl_hook::gui.font;
                GlobalConfig::Instance().fontPath = StringConverter::WstringToUtf8(fontFiles[i].path);
            }
        }
    }
private:
    std::vector<FontInfo> fontFiles;

    static std::vector<FontInfo> GetFontsFromDirectory(const std::wstring& directory) {
        std::vector<FontInfo> fontInfos;

        WIN32_FIND_DATA findFileData;
        HANDLE hFind = FindFirstFile((directory + L"\\*").c_str(), &findFileData);

        if (hFind == INVALID_HANDLE_VALUE)
            return fontInfos;

        do {
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                std::wstring filename = findFileData.cFileName;
                if (filename.find(L".ttf") != std::string::npos || filename.find(L".otf") != std::string::npos) {
                    FontInfo fontInfo;
                    //去除后缀.ttf
                    filename = filename.substr(0, filename.find_last_of(L"."));
                    fontInfo.name = StringConverter::WstringToUtf8(filename);
                    fontInfo.path = directory + L"\\" + filename;
                    fontInfos.push_back(fontInfo);
                }
            }
        } while (FindNextFile(hFind, &findFileData) != 0);

        FindClose(hFind);
        return fontInfos;
    }

};
