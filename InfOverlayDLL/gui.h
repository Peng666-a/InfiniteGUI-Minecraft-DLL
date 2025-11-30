#pragma once
#include "imgui/imgui.h"
class Gui
{
public:
	bool opened = false;
	void init();
	void clean();
	void render();
	ImFont* font = nullptr;
};

