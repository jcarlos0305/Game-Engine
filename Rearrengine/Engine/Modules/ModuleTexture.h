#pragma once

#include "Module.h"

class ModuleTexture : public Module {

public:
	bool Init() override;
	UpdateStatus PreUpdate() override;
	UpdateStatus Update() override;
	UpdateStatus PostUpdate() override;

	unsigned int LoadTexture(const char* path);

	bool CleanUp() override;
};
