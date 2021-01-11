#pragma once

#include "UIWindow.h"

class Information : public UIWindow {
public:
	Information();
	~Information();

	void Draw();

	bool CleanUp();

private:
	bool vsync = true;
};