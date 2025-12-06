#pragma once
#include "Item.h"
#include "UpdateModule.h"
#include <Windows.h>
//
//enum class GameState {
//    Paused,
//    InventoryOpen,
//    ChatTyping,
//    InGUI,
//    InGame
//};


class GameStateDetector : public UpdateModule, public Item{
public:


    GameStateDetector() {
        type = Hidden; // 信息项类型
        multiType = Singleton;    // 信息项是否可以多开
        name = u8"游戏状态检测";
        description = u8"检测游戏当前状态";
        isEnabled = true;
        updateIntervalMs = 10;
        lastUpdateTime = std::chrono::steady_clock::now();
    }
    ~GameStateDetector() {}

    static GameStateDetector& Instance()
    {
        static GameStateDetector instance;
        return instance;
    }

    void Toggle() override;
    void Update() override;
    void Load(const nlohmann::json& j) override;
    void Save(nlohmann::json& j) const override;
    void DrawSettings() override;

    //bool IsPaused() const;          // ESC菜单
    //bool IsInventoryOpen() const;   // 背包
    //bool IsChatTyping() const;      // 聊天输入
    //bool IsInGUI() const;           // 任意GUI
    bool IsInGame() const;          // 在游戏世界中
    bool IsNeedHide() const;        // 是否需要隐藏信息项;
    void ProcessMouseMovement(int dx, int dy);
    bool IsCameraMoving() const;
    float GetCameraSpeed() const;
private:
    //bool DetWindowCenter() const;
    bool IsMouseCursorVisible() const;

    bool hideItemInGui = true;
    //GameState currentState = GameState::Paused;
    bool isInGame = false;
    int centerLevel = 1;

    float movementThreshold = 1.0f; // 小于这个视为静止，用于防抖动
    float cameraSpeed;    // 鼠标移动速度
    bool cameraMoving;
};