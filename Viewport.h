#pragma once

#include "UiComponent.h"

class Viewport : public UiComponent {
public:
	Viewport();
	~Viewport();

	void Draw();

	bool CleanUp();

public:
	bool is_viewport_focused = false;
};