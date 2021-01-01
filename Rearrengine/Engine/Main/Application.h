#pragma once

#include<vector>
#include "Modules/Module.h"
#include "Utils/Globals.h"
#include "Resources/Timer.h"

class ModuleRender;
class ModuleWindow;
class ModuleInput;
class ModuleCamera;
class ModuleDebugDraw;
class ModuleProgram;
class ModuleTexture;
class ModuleModel;
class ModuleEditor;
class ModuleScene;

class Application {
public:

	Application();
	~Application();

	bool Init();
	UpdateStatus Update();
	bool CleanUp();

	void RequestBrowser(const char* url);

public:
	ModuleRender* render = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleDebugDraw* debug_draw = nullptr;
	ModuleProgram* program = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleModel* model = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleScene* scene = nullptr;

	float delta_time = 0.0f;
	float fps = 0.0f;

private:
	Timer* timer = nullptr;
	unsigned int last_time = 0;
	std::vector<Module*> modules;
};

extern Application* App;
