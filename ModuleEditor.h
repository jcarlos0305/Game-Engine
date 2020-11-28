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

	// Clean up
	bool CleanUp();

public:
	Console*       console = nullptr;
	Configuration* configuration = nullptr;
	About*         about = nullptr;

	std::vector<UiComponent*> windows;
};
