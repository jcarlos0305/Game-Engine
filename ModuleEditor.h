#pragma once

#include "Module.h"

class ModuleEditor : public Module {
public:
	bool Init();

	// Update functions
	UpdateStatus PreUpdate();
	UpdateStatus Update();
	UpdateStatus PostUpdate();

	// Clean up
	bool CleanUp();
};
