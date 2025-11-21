#include "ItemManager.h"
#include "TimeItem.h"
#include "FpsItem.h"
#include "BilibiliFansItem.h"
#include "FileCountItem.h"
#include "CounterItem.h"
#include "DanmakuItem.h"
#include "TextItem.h"
#include "GlobalConfig.h"

#include <chrono>


ItemManager::ItemManager()
{
    // 注册默认信息项
    //AddItem(std::make_shared<TimeItem>());
    //AddItem(std::make_shared<FpsItem>());
    //AddItem(std::make_shared<BilibiliFansItem>());
    //AddItem(std::make_shared<FileCountItem>());
    //AddItem(std::make_shared<CounterItem>());
    //AddItem(std::make_shared<DanmakuItem>());
}

void ItemManager::AddItem(std::shared_ptr<Item> item)
{
    items.push_back(std::move(item));
}


// ---------------------------------------------
// 删除信息项（简单版）
// ---------------------------------------------
void ItemManager::RemoveItem(int index)
{
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);

    }

}

void ItemManager::UpdateAll()
{
    auto now = std::chrono::steady_clock::now();

    for (auto& item : items)
    {
        if (!item->isEnabled) continue; // 跳过禁用的模块
        if (auto upd = dynamic_cast<UpdateModule*>(item.get()))
        {
            if (upd->ShouldUpdate())
            {
                upd->Update();
                upd->MarkUpdated();
            }
                
        }
    }
}


// ---------------------------------------------
// 渲染所有信息项（每帧调用）
// ---------------------------------------------
void ItemManager::RenderAll(GlobalConfig* globalConfig, HWND hwnd)
{

    for (auto& item : items) {
        if (!item->isEnabled) continue; // 跳过禁用的模块
        if (auto win = dynamic_cast<WindowModule*>(item.get()))
        {
            win->RenderWindow(hwnd);
        }
    }
}

// ---------------------------------------------
// 从 JSON 加载全部信息项
// ---------------------------------------------
void ItemManager::Load(const nlohmann::json& j)
{
    if (!j.contains("Items")) return;
    for (auto& v : j["Items"])
    {
        std::string type = v["type"].get<std::string>();
        std::unique_ptr<Item> item;

        if (type == "text")
        {
            item = std::make_unique<TextItem>();
        }
        else if (type == "time") {
            item = std::make_unique<TimeItem>();
        }
        else if (type == "fps") {
            item = std::make_unique<FpsItem>();
        }
        else if (type == "bilibili_fans") {
            item = std::make_unique<BilibiliFansItem>();
        }
        else if (type == "file_count") {
            item = std::make_unique<FileCountItem>();
        }
        else if (type == "counter") {
            item = std::make_unique<CounterItem>();
        }
        else if (type == "danmaku") {
            item = std::make_unique<DanmakuItem>();
        }
        else {
            continue;
        }

        item->Load(v);
        AddItem(std::move(item));
    }
}

// ---------------------------------------------
// 保存所有信息项
// ---------------------------------------------
void ItemManager::Save(nlohmann::json& j) const
{
    j["Items"] = nlohmann::json::array();

    for (auto& item : items)
    {
        nlohmann::json v;
        item->Save(v);
        j["Items"].push_back(v);
    }
}