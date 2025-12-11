#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <cmath>

struct ButtonText
{
	const char* text;
	ImFont* font;
};

enum ButtonState
{
	Normal, //普通状态
	Selected, //选中状态
	Hovered, //悬停状态
	Active //按住状态
};

struct TextAnimTarget
{
	float fontSize;
	ImVec2 center;
	ImVec4 color;
	ImVec2 CalculatePos() const //pos不应当作为动画的目标变量。动画只由中心位置、大小、颜色决定
	{
		ImVec2 pos = ImVec2(center.x - fontSize / 2, center.y - fontSize / 2);
		return pos;
	}
	void CalculateCenter(const ImVec2& pos)
	{
		center = ImVec2(pos.x + fontSize / 2, pos.y + fontSize / 2);
	}
};

struct ButtonAnimTarget
{
	ImVec2 size;
	ImVec2 center;
	ImVec4 color;
	ImVec4 borderColor;
	ImVec2 CalculatePos() const
	{
		ImVec2 pos = ImVec2(center.x - size.x / 2, center.y - size.y / 2);
		return pos;
	}
	void CalculateCenter(const ImVec2& pos)
	{
		center = ImVec2(pos.x + size.x / 2, pos.y + size.y / 2);
	}
};

class AnimButtonBase
{
public:
    virtual bool Draw(const bool& windowDragging = false) = 0;

protected:
    // 必须由子类实现
    virtual void SetStateData() = 0;

	ImVec2 screenPos;

    ButtonState m_state = Normal;
    ButtonState lastState = Normal;

    bool initialized = false;
    bool skipAnim = false;

    float animSpeed = 15.0f;

    float m_padding = 8.0f;

	static void DrawBackground(const ButtonAnimTarget &current, const ImDrawFlags& flags = ImDrawFlags_RoundCornersAll)
	{
		ImDrawList* draw = ImGui::GetWindowDrawList();

		ImVec2 pos = current.CalculatePos();
		ImVec2 size = current.size;

		draw->AddRectFilled(
			pos,
			ImVec2(pos.x + size.x, pos.y + size.y),
			ImGui::ColorConvertFloat4ToU32(current.color),
			ImGui::GetStyle().FrameRounding, // 圆角
			flags
		);
	}

	static void DrawBorder(const ButtonAnimTarget& current, const ImDrawFlags& flags = ImDrawFlags_RoundCornersAll)
	{
		ImDrawList* draw = ImGui::GetWindowDrawList();

		ImVec2 pos = current.CalculatePos();
		ImVec2 size = current.size;

		draw->AddRect(
			pos,
			ImVec2(pos.x + size.x, pos.y + size.y),
			ImGui::ColorConvertFloat4ToU32(current.borderColor),
			ImGui::GetStyle().FrameRounding, // 圆角
			flags,
			1.0f // 线宽
		);
	}

	static void DrawShadowText(ImFont* font, float fontSize, const ImVec2& pos, const ImU32& color, const char* text)
	{
		ImDrawList* draw = ImGui::GetWindowDrawList();
		float shadowOffset =/* fontSize * 0.08f*/1.0f;
		float alpha = ImGui::ColorConvertU32ToFloat4(color).w * 0.5f;
		ImU32 ShadowColor = ImGui::ColorConvertFloat4ToU32(ImVec4(0.0f, 0.0f, 0.0f, alpha));
		draw->AddText(
			font,
			fontSize,
			ImVec2(pos.x + shadowOffset, pos.y + shadowOffset),
			ShadowColor,
			text
		);
		draw->AddText(
			font,
			fontSize,
			pos,
			color,
			text
		);
	}

	static void SetNextCursorScreenPos(const ButtonAnimTarget& normal, float padding = 8.0f, ImVec2 screenPos = ImVec2(0, 0)) //下一个控件位置一定由初始位置 + 初始大小 + 边距决定，否则会发生偏移
	{
		ImVec2 nextPos = screenPos;
		nextPos.y = screenPos.y + normal.size.y + padding;
		ImGui::SetCursorScreenPos(nextPos);
	}

    // 插值
    template<typename T>
    static void SmoothLerp(T& cur, const T& target, float damping, float dt)
    {
        float t = 1.f - std::exp(-damping * dt);
        cur = ImLerp(cur, target, t);
    }

	static void LerpButton(ButtonAnimTarget& cur, const ButtonAnimTarget& target, float damping, float deltaTime)
	{
		SmoothLerp(cur.size, target.size, damping, deltaTime);
		SmoothLerp(cur.center, target.center, damping, deltaTime);
		SmoothLerp(cur.color, target.color, damping, deltaTime);
		SmoothLerp(cur.borderColor, target.borderColor, damping, deltaTime);
	}

	static void LerpText(TextAnimTarget& cur, const TextAnimTarget& target, float damping, float deltaTime)
	{
		SmoothLerp(cur.fontSize, target.fontSize, damping, deltaTime);
		SmoothLerp(cur.center, target.center, damping, deltaTime);
		SmoothLerp(cur.color, target.color, damping, deltaTime);
	}

	static bool IsEqual(const ButtonAnimTarget& a, const ButtonAnimTarget& b)
	{
		return AlmostEqual(a.size, a.size)
			&& AlmostEqual(a.center, b.center)
			&& AlmostEqual(a.color, b.color)
			&& AlmostEqual(a.borderColor, b.borderColor);
	}

	static bool IsEqual(const TextAnimTarget& a, const TextAnimTarget& b)
	{
		return AlmostEqual(a.fontSize, b.fontSize)
			&& AlmostEqual(a.center, b.center)
			&& AlmostEqual(a.color, b.color);
	}

	static bool AlmostEqual(float a, float b, float eps = 0.001f)
	{
		return fabsf(a - b) < eps;
	}

	static bool AlmostEqual(const ImVec2& a, const ImVec2& b, float eps = 0.001f)
	{
		return AlmostEqual(a.x, b.x, eps) && AlmostEqual(a.y, b.y, eps);
	}

	static bool AlmostEqual(const ImVec4& a, const ImVec4& b, float eps = 0.001f)
	{
		return AlmostEqual(a.x, b.x, eps)
			&& AlmostEqual(a.y, b.y, eps)
			&& AlmostEqual(a.z, b.z, eps)
			&& AlmostEqual(a.w, b.w, eps);
	}

};
