#pragma once
#include "Item.h"
#include "RenderModule.h"
class Motionblur : public Item, public RenderModule {
public:
    Motionblur() {
        type = Util; // 信息项类型
        multiType = Singleton;    // 信息项是否可以多开
        name = u8"动态模糊";
        description = u8"动态模糊";
        isEnabled = false;
    }
    ~Motionblur() {}

    static Motionblur& Instance()
    {
        static Motionblur instance;
        return instance;
    }

    void Toggle() override;
    void Render() override;
    void Load(const nlohmann::json& j) override;
    void Save(nlohmann::json& j) const override;
    void DrawSettings() override;

    void initialize_texture(const int width, const int height);
    void initialize_quad();
	void initialize_shader();

	void resize_texture(int width, int height);
	void draw_texture(float blurriness_value) const;
	void copy_to_history() const;
	void copy_to_current() const;

    void velocity_adaptive_blur(bool cameraMoving, float velocity, float value, float* cur_blurriness_value) const;
    float cur_blurriness_value = 20.0f;
    bool applayOnMenu = true;
private:
    uint32_t shader_program_;

    uint32_t current_texture_;
    uint32_t history_texture_;

    uint32_t quad_vao_;
    uint32_t quad_vbo_;

    int32_t texture_width_;
    int32_t texture_height_;


    float blurriness_value = 20.0f;
    bool clear_color = false;
    bool velocityAdaptive = true;

};