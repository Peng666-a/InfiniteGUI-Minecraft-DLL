#pragma once

#include <string>
#include <queue>
#include <vector>
#include <imgui.h>

class DanmakuWindow {
public:
    DanmakuWindow(int maxMessages = 100, ImVec2 position = ImVec2(50, 50), float width = 600, float height = 400);

    void AddMessage(const std::string& message);
    void AddGiftMessage(const std::string& giftMessage);
    void AddEnterRoomMessage(const std::string& enterMessage);

    void Draw();

    void SetPosition(const ImVec2& newPos);
    void SetMaxMessages(int newMax);

private:
    std::queue<std::string> messages;
    std::vector<std::string> enterMessages;
    std::vector<std::string> giftMessages;
    int maxMessages;
    ImVec2 position;
    float width, height;
};