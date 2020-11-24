#pragma once

#include "Module.h"

class ModuleRender : public Module {
public:
	bool Init();

	UpdateStatus PreUpdate();
	UpdateStatus Update();
	UpdateStatus PostUpdate();

	bool CleanUp();

	void WindowResized(unsigned width, unsigned height);
	void* context = nullptr;

};
