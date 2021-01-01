#pragma once

#include "Utils/Globals.h"
#include "UIWindow.h"

class About : public UIWindow {
public:
	About();
	~About();

	void Draw();

	bool CleanUp();

};