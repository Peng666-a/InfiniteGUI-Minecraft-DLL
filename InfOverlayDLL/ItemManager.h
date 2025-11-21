#pragma once
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "Item.h"
#include "GlobalConfig.h"

class ItemManager {
public:
    ItemManager();

    void AddItem(std::shared_ptr<Item> item);
    void RemoveItem(int index);

    void UpdateAll();

    void RenderAll(GlobalConfig* globalConfig, HWND hwnd);

    void Load(const nlohmann::json& j);
    void Save(nlohmann::json& j) const;

    std::vector<std::shared_ptr<Item>>& GetItems() { return items; }

private:
    std::vector<std::shared_ptr<Item>> items;
};