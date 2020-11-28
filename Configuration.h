#pragma once

#include "Globals.h"
#include "UiComponent.h"

class Configuration : public UiComponent {
public:
	Configuration();
	~Configuration();
	
	void Draw();

	bool CleanUp();

};