#include "WindowSnapper.h"
#include <cmath>

SnapResult WindowSnapper::ComputeSnap(
    const ImVec2& pos,
    const ImVec2& size,
    float screenW,
    float screenH,
    float snapDist)
{
    SnapResult r;
    r.snappedPos = pos;

    float right = pos.x + size.x;
    float bottom = pos.y + size.y;

    float cx = pos.x + size.x * 0.5f;
    float cy = pos.y + size.y * 0.5f;

    // ±ßÔµÎü¸½
    if (fabs(pos.x) < snapDist) {
        r.snappedPos.x = 0;
        r.snapLeft = true;
    }
    if (fabs(right - screenW) < snapDist) {
        r.snappedPos.x = screenW - size.x;
        r.snapRight = true;
    }
    if (fabs(pos.y) < snapDist) {
        r.snappedPos.y = 0;
        r.snapTop = true;
    }
    if (fabs(bottom - screenH) < snapDist) {
        r.snappedPos.y = screenH - size.y;
        r.snapBottom = true;
    }

    // ÖÐÐÄÎü¸½
    if (fabs(cx - screenW * 0.5f) < snapDist) {
        r.snappedPos.x = screenW * 0.5f - size.x * 0.5f;
        r.snapCenterX = true;
    }
    if (fabs(cy - screenH * 0.5f) < snapDist) {
        r.snappedPos.y = screenH * 0.5f - size.y * 0.5f;
        r.snapCenterY = true;
    }

    return r;
}

void WindowSnapper::DrawGuides(const SnapResult& r, float screenW, float screenH)
{
    auto draw = ImGui::GetForegroundDrawList();
    ImU32 color = IM_COL32(120, 180, 255, 150);

    if (r.snapLeft)
        draw->AddLine(ImVec2(0, 0), ImVec2(0, screenH), color, 2.0f);

    if (r.snapRight)
        draw->AddLine(ImVec2(screenW, 0), ImVec2(screenW, screenH), color, 2.0f);

    if (r.snapTop)
        draw->AddLine(ImVec2(0, 0), ImVec2(screenW, 0), color, 2.0f);

    if (r.snapBottom)
        draw->AddLine(ImVec2(0, screenH), ImVec2(screenW, screenH), color, 2.0f);

    if (r.snapCenterX)
        draw->AddLine(ImVec2(screenW * 0.5f, 0), ImVec2(screenW * 0.5f, screenH), color, 2.0f);

    if (r.snapCenterY)
        draw->AddLine(ImVec2(0, screenH * 0.5f), ImVec2(screenW, screenH * 0.5f), color, 2.0f);
}