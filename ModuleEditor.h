#pragma once

#include "Module.h"
#include "UiComponent.h"
#include<vector>

class Console;
class Configuration;
class About;

class ModuleEditor : public Module {
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init();

	// Update functions
	UpdateStatus PreUpdate();
	UpdateStatus Update();
	UpdateStatus PostUpdate();

	void AddLog(const char* log);

	void RenderViewport();

	// Clean up
	bool CleanUp();

public:
	Console*       console = nullptr;
	Configuration* configuration = nullptr;
	About*         about = nullptr;

	bool           is_viewport_focused = false;

	std::vector<UiComponent*> windows;
};
