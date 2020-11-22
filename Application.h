#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleInput;
class ModuleCamera;
class ModuleDebugDraw;
class ModuleProgram;
class ModuleTexture;
class ModuleModel;

class Application {
public:

	Application();
	~Application();

	bool Init();
	UpdateStatus Update();
	bool CleanUp();

public:
	ModuleRender* render = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleDebugDraw* debug_draw = nullptr;
	ModuleProgram* program = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleModel* model = nullptr;

	float delta_time = 0.0f;

private:
	float last_time = 0.0f;
	std::list<Module*> modules;
};

extern Application* App;
