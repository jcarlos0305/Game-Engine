#pragma once

#include "../Utils/Globals.h"
#include "UIWindow.h"

class Configuration : public UIWindow {
public:
	Configuration();
	~Configuration();
	
	void Draw();

	bool CleanUp();

};