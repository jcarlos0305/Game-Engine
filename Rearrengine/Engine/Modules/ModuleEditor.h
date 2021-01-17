#pragma once

#include "Module.h"
#include "UI/UIWindow.h"
#include<vector>

class Console;
class Configuration;
class About;
class Viewport;
class Information;
class Hierarchy;

class ModuleEditor : public Module {
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init() override;

	// Update functions
	UpdateStatus PreUpdate() override;
	UpdateStatus Update() override;
	UpdateStatus PostUpdate() override;

	void AddLog(const char* log);
	Configuration* GetConfiguration() { return configuration; };

	// Clean up
	bool CleanUp() override;

public:
	Console* console = nullptr;
	Configuration* configuration = nullptr;
	About* about = nullptr;
	Viewport* viewport = nullptr;
	Information* information = nullptr;
	Hierarchy* hierarchy = nullptr;

	std::vector<UIWindow*> windows;
};
