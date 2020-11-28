#pragma once

#include "ImGui/imgui.h"
#include "UiComponent.h"

class Console : public UiComponent {
public:
	Console();
	~Console();

	void Clear();

	void AddLog(const char* fmt);
	void Draw();

public:
	bool             auto_scroll = true;
	ImVector<char*>  buffer;
	ImVector<int>    line_offsets;
};