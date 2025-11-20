#include "Module.h"
#include "WindowModule.h"
#include "AffixModule.h"
#include <string>

class Text : public Module, public WindowModule, public AffixModule
{
public:
    Text() {
        type = ModuleType::MultiInstance;
        name = u8"文字显示";
        description = u8"没别的，显示文字";
        text = u8"请输入文本";
    }

    const char* GetTypeName() const override { return "Text"; }

    void DrawContent() override;
    void DrawSettings() override;
    void Load(const nlohmann::json& j) override;
    void Save(nlohmann::json& j) const override;

    std::string text;
};