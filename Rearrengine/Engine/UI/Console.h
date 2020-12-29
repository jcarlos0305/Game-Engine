#pragma once

#include "ImGui/imgui.h"
#include "UIWindow.h"

class Console : public UIWindow {
public:
	Console();
	~Console();

	void Clear();

	void AddLog(const char* fmt);
	void Draw();

	bool CleanUp();

public:
	bool             auto_scroll = true;
	ImVector<char*>  buffer;
};