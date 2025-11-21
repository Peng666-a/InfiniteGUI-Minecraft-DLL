#pragma once
#include "ItemManager.h"
#include "TextItem.h"
#include "TimeItem.h"
#include "FileCountItem.h"
#include "BilibiliFansItem.h"
#include "CounterItem.h"
#include "DanmakuItem.h"
#include "FpsItem.h"


class MainUI {
public:

    bool open = false;

    MainUI(ItemManager* manager);

    void Render(GlobalConfig* global);

    void Toggle(bool open);

    void Toggle();

private:
    ItemManager* manager;

    void DrawItemList();
    void DrawItemEditor(Item* item);

};