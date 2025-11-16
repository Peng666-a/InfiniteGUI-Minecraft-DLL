#pragma once
#include "imgui/imgui.h"

struct SnapResult {
    ImVec2 snappedPos;
    bool snapLeft = false;
    bool snapRight = false;
    bool snapTop = false;
    bool snapBottom = false;
    bool snapCenterX = false;
    bool snapCenterY = false;
};

class WindowSnapper
{
public:
    static SnapResult ComputeSnap(
        const ImVec2& pos,
        const ImVec2& size,
        float screenW,
        float screenH,
        float snapDist);

    static void DrawGuides(const SnapResult& r, float screenW, float screenH);
};