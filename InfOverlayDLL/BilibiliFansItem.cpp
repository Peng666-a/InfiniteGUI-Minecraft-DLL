#include "BilibiliFansItem.h"
#include "HttpClient.h"
#include "ImGuiStd.h"
#include "ImGui\imgui_internal.h"
#include <nlohmann/json.hpp>
#include "AudioManager.h"

void BilibiliFansItem::Update()
{
    if (uid <= 0) {
        fansCount = -1;
        return;
    }

    // 生成 URL（注意使用 wstring 版）
    std::wstring url =
        L"https://api.bilibili.com/x/relation/stat?vmid=" +
        std::to_wstring(uid);

    std::string response;
    bool ok = HttpClient::HttpGet(url, response);

    int resultFans = -1;

    if (ok)
    {
        try {
            auto j = nlohmann::json::parse(response);
            resultFans = j["data"]["follower"].get<int>();
        }
        catch (...) {
            resultFans = -1;
        }
    }

    fansCount = resultFans;

    if (fansCount < 0) {
        ImGuiStd::TextShadow(u8"粉丝数获取失败");
        return;
    }
    if (fansCount > lastFansCount)
    {
        color.color = ImVec4(0.1f, 1.0f, 0.1f, 1.0f); //绿色
        lastFansCount = fansCount;
        if (isPlaySound) AudioManager::Instance().playSound("bilibilifans\\bilibilifans_up.wav", soundVolume);
    }
    else if (fansCount < lastFansCount)
    {
        color.color = ImVec4(1.0f, 0.1f, 0.1f, 1.0f); //红色
        lastFansCount = fansCount;
        if (isPlaySound) AudioManager::Instance().playSound("bilibilifans\\bilibilifans_down.wav", soundVolume);
    }

}

void BilibiliFansItem::DrawContent()
{
    ImVec4 targetTextColor = ImGui::GetStyleColorVec4(ImGuiCol_Text);

    //获取io
    ImGuiIO& io = ImGui::GetIO();

    //计算速度
    float speed = 3.0f * io.DeltaTime;
    color.color = ImLerp(color.color, targetTextColor, speed);

    ImGuiStd::TextColoredShadow(color.color, (prefix + std::to_string(fansCount) + suffix).c_str());
}

void BilibiliFansItem::DrawSettings()
{
    DrawModuleSettings();
    static std::string uidStr = std::to_string(uid);
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
            uid = std::stoll(uidStr);
    }
    if (ImGui::CollapsingHeader(u8"通用设置"))
    {
        DrawWindowSettings();
        DrawAffixSettings();
        DrawSoundSettings();
    }
}

void BilibiliFansItem::Load(const nlohmann::json& j)
{
    LoadItem(j);
    LoadAffix(j);
    LoadWindow(j);
    LoadSound(j);
    if (j.contains("uid")) uid = j["uid"];
    if (j.contains("fansCount")) fansCount = j["fansCount"];
    lastFansCount = fansCount;

}

void BilibiliFansItem::Save(nlohmann::json& j) const
{
    SaveItem(j);
    SaveAffix(j);
    SaveWindow(j);
    SaveSound(j);

    j["uid"] = uid;
    j["fansCount"] = fansCount;
}