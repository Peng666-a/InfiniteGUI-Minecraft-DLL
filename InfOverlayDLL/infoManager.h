#pragma once
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>
#include "InfoItem.h"
#include "GlobalConfig.h"

class InfoManager {
public:
    InfoManager();

    void AddItem(std::shared_ptr<InfoItem> item);
    void RemoveItem(int index);

    void UpdateAll();

    void RenderAll(GlobalConfig* globalConfig, HWND hwnd);

    void Load(const nlohmann::json& j);
    void Save(nlohmann::json& j) const;

    std::vector<std::shared_ptr<InfoItem>>& GetItems() { return items; }

private:
    std::vector<std::shared_ptr<InfoItem>> items;
};