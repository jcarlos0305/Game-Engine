#pragma once

#include "Module.h"

class ModuleRender : public Module {
public:
	ModuleRender();
	~ModuleRender();
	
	bool Init();

	UpdateStatus PreUpdate();
	UpdateStatus Update();
	UpdateStatus PostUpdate();

	void RenderViewport(unsigned int width, unsigned int height);

	bool CleanUp();

	void WindowResized(unsigned width, unsigned height);
	
	
	void* context = nullptr;
	unsigned int fbo = 0;
	unsigned int texture = 0;
	unsigned int rbo = 0;
};
