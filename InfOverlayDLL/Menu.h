#pragma once
#include "ItemManager.h"
#include "TextItem.h"
#include "TimeItem.h"
#include "FileCountItem.h"
#include "BilibiliFansItem.h"
#include "CounterItem.h"
#include "DanmakuItem.h"
#include "FpsItem.h"

enum MenuState {
    MENU_STATE_MAIN,
    MENU_STATE_SETTINGS,
};

enum SETTING_STATE {
    SETTING_STATE_MODULES,
    SETTING_STATE_GENERAL,
    SETTING_STATE_ABOUT,
};

class Menu {
public:

    bool open = false;

    static Menu& Instance()
    {
        static Menu instance;
        return instance;
    }
    Menu();

    void Render();

    void Toggle(bool open);

    void Toggle();

private:

    void DrawItemList();
    void DrawItemEditor(Item* item);

};