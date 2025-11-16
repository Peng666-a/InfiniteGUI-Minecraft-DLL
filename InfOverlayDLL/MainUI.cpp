#include "MainUI.h"
#include "imgui/imgui.h"
#include "ImGuiStd.h"
#include "ConfigManager.h"
#include "GlobalConfig.h"
#include "StringConverter.h"

struct FontInfo {
    std::string name;
    std::wstring path;
};

std::vector<FontInfo> GetFontsFromDirectory(const std::wstring& directory) {
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
                fontInfo.name = StringConverter::WstringToUtf8(filename);
                fontInfo.path = directory + L"\\" + filename;
                fontInfos.push_back(fontInfo);
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
    return fontInfos;
}

void ShowFontSelection(GlobalConfig* globalConfig) {
    static std::vector<FontInfo> fontFiles;

    // Get font files if not loaded yet
    if (fontFiles.empty()) {
        fontFiles = GetFontsFromDirectory(L"C:\\Windows\\Fonts");
        ////获取用户名
        //std::wstring username = L"";
        //DWORD usernameSize = 0;

        // 获取用户名
        wchar_t username[256]; // 确保足够空间来存储用户名
        DWORD usernameSize = sizeof(username) / sizeof(username[0]);
        GetUserNameW(username, &usernameSize);
        std::vector<FontInfo> userFonts = GetFontsFromDirectory(L"C:\\Users\\" + std::wstring(username) + L"\\AppData\\Local\\Microsoft\\Windows\\Fonts");
        fontFiles.insert(fontFiles.end(), userFonts.begin(), userFonts.end());
    }

    if(ImGui::CollapsingHeader(u8"字体选择", ImGuiTreeNodeFlags_FramePadding))
    {
        ImGui::BeginGroup();
        if (ImGui::Selectable(u8"默认字体-Uranus_Pixel_11Px (重启生效)")) {
            // Load the selected font
            globalConfig->fontPath = "default";
        }

        for (size_t i = 0; i < fontFiles.size(); ++i) {
            if (ImGui::Selectable(fontFiles[i].name.c_str())) {
                // Load the selected font
                ImGuiIO& io = ImGui::GetIO();
                io.FontDefault = io.Fonts->AddFontFromFileTTF(StringConverter::WstringToUtf8(fontFiles[i].path).c_str(), 20.0f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesChineseFull());
                globalConfig->fontPath = StringConverter::WstringToUtf8(fontFiles[i].path);
            }
        }
        ImGui::EndGroup();
    }

}

MainUI::MainUI(InfoManager* manager)
    : manager(manager)
{
}

void MainUI::Render(GlobalConfig* globalConfig)
{

    // 首次渲染时，记录圆角状态
    static int firstRender = 5;
    static bool prevRoundCorner = false;
    static bool isStyleEditorShow = false;
    if (isStyleEditorShow)
    {

        ImGui::ShowStyleEditor();
    }

    //使窗口显示在屏幕中间
    ImGui::SetNextWindowPos(ImVec2((ImGui::GetIO().DisplaySize.x - ImGui::GetIO().DisplaySize.x / 2), (ImGui::GetIO().DisplaySize.y - ImGui::GetIO().DisplaySize.y / 2)), ImGuiCond_Once, ImVec2(0.5f, 0.5f));


    ImGui::Begin(u8"主控制面板", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);

    ImGui::Text(u8"主控制面板");

    ImGui::SameLine();

    if (ImGui::Button(u8"保存配置"))
        ConfigManager::Save(ConfigManager::GetConfigPath(), *globalConfig, *manager);


    ImGui::SameLine();

    //将退出按钮显示在右上角
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 45);

    if (ImGui::Button("  X  "))
    {
        PostQuitMessage(0);
    }

    ImGui::SameLine();

    //将退出按钮显示在右上角
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 90);

    if (ImGui::Button("  +  "))
    {
        isStyleEditorShow = !isStyleEditorShow;
    }

    ImGui::Separator();

    if (ImGui::CollapsingHeader(u8"全局设置", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding))
    {
        if (ImGui::SliderFloat(u8"圆角半径", &globalConfig->roundCornerRadius, 0.0f, 10.0f, "%.1f"))
        {
            ImGuiStyle& style = ImGui::GetStyle();
            style.WindowRounding = globalConfig->roundCornerRadius;
            style.FrameRounding = globalConfig->roundCornerRadius;
            style.GrabRounding = globalConfig->roundCornerRadius;
            style.ScrollbarRounding = globalConfig->roundCornerRadius;
            style.TabRounding = globalConfig->roundCornerRadius;
            style.ChildRounding = globalConfig->roundCornerRadius;
            style.PopupRounding = globalConfig->roundCornerRadius;
        }
        // 设置主UI快捷键

        static const char* keys[] = {
    "None",
    "Mouse 1",
    "Mouse 2",
    "CN",
    "Mouse 3",
    "Mouse 4",
    "Mouse 5",
    "-##1",
    "Back",
    "Tab",
    "-##2",
    "-##3",
    "CLR",
    "Enter",
    "-##4",
    "-##5",
    "Shift",
    "Ctrl",
    "Menu",
    "Pause",
    "Caps Lock",
    "KAN",
    "-##6",
    "JUN",
    "FIN",
    "HAN",
    "-##7",
    "Escape",
    "CON",
    "NCO",
    "ACC",
    "MAD",
    "Space",
    "PGU",
    "PGD",
    "End",
    "Home",
    "Left",
    "Up",
    "Right",
    "Down",
    "SEL",
    "PRI",
    "EXE",
    "SNAPSHOT",
    "INS",
    "Delete",
    "HEL",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "-##8",
    "-##9",
    "-##10",
    "-##11",
    "-##12",
    "-##13",
    "-##14",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "LWIN",
    "RWIN",
    "APP",
    "-##15",
    "SLE",
    "Numpad 0",
    "Numpad 1",
    "Numpad 2",
    "Numpad 3",
    "Numpad 4",
    "Numpad 5",
    "Numpad 6",
    "Numpad 7",
    "Numpad 8",
    "Numpad 9",
    "MUL",
    "ADD",
    "SEP",
    "MIN",
    "DECIMAL",
    "DIV",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "F16",
    "F17",
    "F18",
    "F19",
    "F20",
    "F21",
    "F22",
    "F23",
    "F24",
    "-##16",
    "-##17",
    "-##18",
    "-##19",
    "-##20",
    "-##21",
    "-##22",
    "-##23",
    "NUM",
    "SCR",
    "EQU",
    "MAS",
    "TOY",
    "LOYA",
    "ROYA",
    "-##24",
    "-##25",
    "-##26",
    "-##27",
    "-##28",
    "-##29",
    "-##30",
    "-##31",
    "-##32",
    "LShift",
    "RShift",
    "LCtrl",
    "RCtrl",
    "LAlt",
    "RAlt",
    "-##33",
    "-##34",
    "-##35",
    "-##36",
    "-##37",
    "-##38",
    "-##39",
    "-##40",
    "-##41",
    "-##42",
    "-##43",
    "-##44",
    "-##45",
    "-##46",
    "-##47",
    "-##48",
    "-##49",
    "-##50",
    "-##51",
    "-##52",
    ";",
    "=",
    ",",
    "-",
    ".",
    "/",
    "`",
    "-##53",
    "-##54",
    "-##55",
    "-##56",
    "-##57",
    "-##58",
    "-##59",
    "-##60",
    "-##61",
    "-##62",
    "-##63",
    "-##64",
    "-##65",
    "-##66",
    "-##67",
    "-##68",
    "-##69",
    "-##70",
    "-##71",
    "-##72",
    "-##73",
    "-##74",
    "-##75",
    "-##76",
    "-##77",
    "-##78",
    "[",
    "\\",
    "]",
    "'"
        };


        //对照VK_CODE枚举值，找到对应的键名
        static std::string menuKeyStr = keys[globalConfig->menuKey];
        static bool binding = false;

        ImGui::Text(u8"UI快捷键：");

        ImGui::SameLine();

        if (ImGui::Button(menuKeyStr.c_str(), ImVec2(100, 0)))
        {
            binding = true;
        }
        if (binding)
        {
            ImGui::OpenPopup("KeyBinding");

        }
        if (ImGui::BeginPopup("KeyBinding"))
        {
            ImGui::Text(u8"绑定快捷键");
            ImGui::Separator();
            for (int i = 0; i < IM_ARRAYSIZE(keys); i++)
            {
                std::string keyStr = keys[i];
                if (keyStr[0] == '-')
                {
                    continue;
                }
                if (ImGui::Selectable(keyStr.c_str()))
                {
                    globalConfig->menuKey = i;
                    menuKeyStr = keyStr;
                    binding = false;
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::IsMouseClicked(1))
                {
                    binding = false;
                    ImGui::CloseCurrentPopup();
                    break;
                }
                    
            }
            ImGui::EndPopup();
        }

        ShowFontSelection(globalConfig);

    }

    ImGui::Separator();

    // 添加各种信息项按钮

    if (ImGui::Button(u8"添加 文本 TextItem")) {
        manager->AddItem(std::make_unique<TextItem>());
    }

    if (ImGui::Button(u8"添加 时间 TimeItem")) {
        manager->AddItem(std::make_unique<TimeItem>());
    }

    if (ImGui::Button(u8"添加 FPS显示 FpsItem")) {
        manager->AddItem(std::make_unique<FpsItem>());
    }

    if (ImGui::Button(u8"添加 文件数量 FileCountItem")) {
        manager->AddItem(std::make_unique<FileCountItem>());
    }

    if (ImGui::Button(u8"添加 B站粉丝数 BilibiliFansItem")) {
        auto p = std::make_unique<BilibiliFansItem>();
        p->uid = 399194206; // 默认设置为你的 UID
        manager->AddItem(std::move(p));
    }

    if (ImGui::Button(u8"添加 B站弹幕显示 BilibiliDanmakuItem")) {
        auto p = std::make_unique<DanmakuItem>();
        //p->logPath = ConfigManager::GetRunPath() + "\\lastrun.txt";
        manager->AddItem(std::move(p));
    }


    ImGui::Separator();
    DrawItemList();

    ImGui::End();
}

void MainUI::DrawItemList()
{
    auto& items = manager->GetItems();

    for (int i = 0; i < items.size(); i++)
    {
        InfoItem* item = items[i].get();

        ImGui::Checkbox(("##" + std::to_string(i)).c_str(), &item->isEnabled);
        ImGui::SameLine();

        ImGui::Text("[%d] %s", i, item->windowTitle.c_str());
        ImGui::SameLine();
        ImGui::PushID(i);

        if (ImGui::Button(u8"删除"))
        {
            manager->RemoveItem(i);
            ImGui::PopID();
            break;
        }

        ImGui::SameLine();
        if (ImGui::Button(u8"设置"))
        {
            ImGui::OpenPopup("ItemEditor");
        }

        if (ImGui::BeginPopup("ItemEditor"))
        {
            DrawItemEditor(item);
            ImGui::EndPopup();
        }

        ImGui::PopID();
        ImGui::SameLine();
        //避免冲突

        std::string clickThroughStr = u8"固定##" + std::to_string(i);

        ImGui::Checkbox(clickThroughStr.c_str(), &item->clickThrough);
    }
}

void MainUI::DrawItemEditor(InfoItem* item)
{
    ImGui::Text(u8"编辑项：%s", item->windowTitle.c_str());

    // 根据不同类型显示不同配置项

    if (auto t = dynamic_cast<TextItem*>(item)) {
        Draw_TextItemSettings(t);
    }
    else if (auto t = dynamic_cast<TimeItem*>(item)) {
        Draw_TimeItemSettings(t);
    }
    else if (auto f = dynamic_cast<FpsItem*>(item)) {
        Draw_FpsItemSettings(f);
    }
    else if (auto f = dynamic_cast<FileCountItem*>(item)) {
        Draw_FileCountItemSettings(f);
    }
    else if (auto b = dynamic_cast<BilibiliFansItem*>(item)) {
        Draw_BilibiliItemSettings(b);
    }
    else if (auto d = dynamic_cast<DanmakuItem*>(item)) {
        Draw_DanmakuItemSettings(d);
    }

    // 通用设置
    if (ImGui::CollapsingHeader(u8"通用设置"))
    {
        ImGui::Checkbox(u8"固定", &item->clickThrough);

        ImGui::Checkbox(u8"显示边框", &item->showBorder);


        ImGui::SliderFloat(u8"背景透明度", &item->alpha, 0.0f, 1.0f, "%.1f");

        ImGui::Checkbox(u8"自定义窗口大小", &item->isCustomSize);
        if (item->isCustomSize) {
            ImGui::InputFloat(u8"宽度", &item->width, 1.0f, 1.0f, "%.1f");
            ImGui::InputFloat(u8"高度", &item->height, 1.0f, 1.0f, "%.1f");
        }
        ImGui::InputFloat(u8"窗口 X", &item->x, 1.0f, 1.0f, "%.1f");
        ImGui::InputFloat(u8"窗口 Y", &item->y, 1.0f, 1.0f, "%.1f");

        ImGui::InputFloat(u8"字体大小", &item->fontSize, 1.0f, 1.0f, "%.1f");


        ImGui::InputInt(u8"刷新间隔(毫秒)", &item->refreshIntervalMs);
        ImGuiStd::InputTextStd(u8"前缀", item->prefix);
        ImGuiStd::InputTextStd(u8"后缀", item->suffix);
    }
}

void MainUI::Draw_TextItemSettings(TextItem* item)
{
    ImGuiStd::InputTextStd(u8"文本内容", item->text);
}

void MainUI::Draw_TimeItemSettings(TimeItem* item)
{
    ImGui::Text(u8"TimeItem 无额外设置");
}

void MainUI::Draw_FpsItemSettings(FpsItem* item)
{
    ImGui::Text(u8"FpsItem 无额外设置");
}

void MainUI::Draw_FileCountItemSettings(FileCountItem* item)
{

    ImGuiStd::InputTextStd(u8"文件夹路径", item->folderPath);
    ImGui::Checkbox(u8"递归扫描(包括子文件夹)", &item->recursive);
    ImGuiStd::InputTextStd(u8"扩展名过滤 (.txt)", item->extensionFilter);
}

void MainUI::Draw_BilibiliItemSettings(BilibiliFansItem* item)
{
    static std::string uidStr = std::to_string(item->uid);
    ImGuiStd::InputTextStd(u8"B站 UID", uidStr);
    ImGui::SameLine();
    if (ImGui::Button(u8"确定"))
    {
        if (uidStr.empty())
        {
            uidStr = u8"不能输入空值"; // 默认设置为你的 UID
        }
        else if (uidStr.find_first_not_of("0123456789") != std::string::npos)
        {
            uidStr = u8"只能输入数字"; // 输入非数字
        }
        else
            item->uid = std::stoll(uidStr);
    }
}

void MainUI::Draw_DanmakuItemSettings(DanmakuItem* item)
{
    ImGuiStd::InputTextStd(u8"弹幕日志文件路径", item->logPath);
    ImGui::InputInt(u8"最大弹幕数", &item->maxDanmakuCount);
}