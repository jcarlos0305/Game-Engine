#pragma once

#include "Module.h"

class ModuleRender : public Module {
public:
	ModuleRender();
	~ModuleRender();

	bool Init() override;

	UpdateStatus PreUpdate() override;
	UpdateStatus Update() override;
	UpdateStatus PostUpdate() override;

	void RenderToViewport(unsigned int width, unsigned int height);

	bool CleanUp() override;

	void EnableVsync(bool enabled);

	void* context = nullptr;
	unsigned int fbo = 0;
	unsigned int texture = 0;
	unsigned int rbo = 0;
};
