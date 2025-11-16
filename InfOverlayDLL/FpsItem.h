#include "InfoItem.h"
class FpsItem : public InfoItem
{
public:
    FpsItem() {
        windowTitle = "FPS Count";
        refreshIntervalMs = 1000;   // 默认1秒刷新
    }
    // InfoItem 接口
    virtual void Update() override; // 在后台线程调用，计算 smoothedFPS
    virtual void DrawContent() override; // 在渲染线程调用，绘制内容 (被 RenderWindow 调用)
    virtual void Load(const nlohmann::json& j) override;
    virtual void Save(nlohmann::json& j) const override;

private:
    // 帧率计数器
    int frameCount = 0;
    float FPS = 0.0f;
};