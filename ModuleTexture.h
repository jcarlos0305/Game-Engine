#pragma once

#include "Module.h"

class ModuleTexture : public Module {

public:
	bool Init();
	UpdateStatus PreUpdate();
	UpdateStatus Update();
	UpdateStatus PostUpdate();

	unsigned int LoadTexture(const char* path);

	bool CleanUp();
};
