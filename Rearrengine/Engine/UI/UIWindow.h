#pragma once

#include "Utils/Globals.h"

class UIWindow {
public:

	UIWindow() {}
	virtual ~UIWindow() {}

	virtual void Draw() {};
	inline  void Show(bool* new_state) { visible = new_state; };

	virtual bool CleanUp() { return true; };

public:
	bool visible = false;
	char* title = "";
};