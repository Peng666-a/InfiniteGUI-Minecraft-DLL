#include "DanmakuWindow.h"
#include <imgui.h>
#include <queue>
#include <string>
#include <vector>

DanmakuWindow::DanmakuWindow(int maxMessages, ImVec2 position, float width, float height)
    : maxMessages(maxMessages), position(position), width(width), height(height) {
}

void DanmakuWindow::AddMessage(const std::string& message) {
    if (messages.size() >= maxMessages) {
        messages.pop();
    }
    messages.push(message);
}

void DanmakuWindow::AddGiftMessage(const std::string& giftMessage) {
    if (giftMessages.size() >= maxMessages) {
        giftMessages.erase(giftMessages.begin());
    }
    giftMessages.push_back(giftMessage);
}

void DanmakuWindow::AddEnterRoomMessage(const std::string& enterMessage) {
    enterMessages.push_back(enterMessage);
}

void DanmakuWindow::Draw() {
    ImGui::SetNextWindowPos(position, ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Once);
    ImGui::Begin("Danmaku Window", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    // 绘制进场信息
    for (const auto& msg : enterMessages) {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%s", msg.c_str());
    }

    // 绘制礼物信息
    for (const auto& msg : giftMessages) {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", msg.c_str());
    }

    // 绘制弹幕信息
    ImGui::BeginChild("Scrolling", ImVec2(0, -30), true, ImGuiWindowFlags_NoScrollbar);
    while (!messages.empty()) {
        ImGui::Text("%s", messages.front().c_str());
        messages.pop();
    }
    ImGui::EndChild();

    ImGui::End();
}

void DanmakuWindow::SetPosition(const ImVec2& newPos) { position = newPos; }
void DanmakuWindow::SetMaxMessages(int newMax) { maxMessages = newMax; }