#pragma once

#include "UIWindow.h"

class Viewport : public UIWindow {
public:
	Viewport();
	~Viewport();

	void Draw();

	bool CleanUp();

public:
	bool is_viewport_focused = false;
};