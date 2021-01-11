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

<<<<<<< HEAD
	void WindowResized(unsigned width, unsigned height);
	
=======
	void EnableVsync(bool enabled);

>>>>>>> master
	void* context = nullptr;
	unsigned int fbo = 0;
	unsigned int texture = 0;
	unsigned int rbo = 0;

	bool showQuad = true;
};
