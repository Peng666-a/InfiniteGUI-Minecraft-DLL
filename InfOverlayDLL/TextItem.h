#include "InfoItem.h"
#include <string>

class TextItem : public InfoItem
{
public:
    TextItem() {
        windowTitle = "Text";
        refreshIntervalMs = -1;  // Ä¬ÈÏ1ÃëË¢ÐÂ
    }

    void Update() override;
    void DrawContent() override;
    void Load(const nlohmann::json& j) override;
    void Save(nlohmann::json& j) const override;

    std::string text;
};