#pragma once
#include "../Main/Application.h"
#include "../Modules/ModuleWindow.h"
#include "../Modules/ModuleRender.h"
#include "../Modules/ModuleInput.h"
#include "../Modules/ModuleCamera.h"
#include "../Modules/ModuleProgram.h"
#include "../Modules/ModuleTexture.h"
#include "../Modules/ModuleModel.h"
#include "../Modules/ModuleEditor.h"
#include "../Modules/ModuleScene.h"

#include "../../Debug Draw/ModuleDebugDraw.h"

#include "../Utils/LeakTest.h"

using namespace std;

Application::Application() {
	modules.reserve(9);
	//The modules Init/start/update in this order
	modules.push_back(window = new ModuleWindow());
	modules.push_back(camera = new ModuleCamera());
	modules.push_back(texture = new ModuleTexture());
	modules.push_back(program = new ModuleProgram());
	modules.push_back(scene = new ModuleScene());
	modules.push_back(render = new ModuleRender());
	modules.push_back(model = new ModuleModel());
	modules.push_back(debug_draw = new ModuleDebugDraw());
	modules.push_back(editor = new ModuleEditor());
	modules.push_back(input = new ModuleInput());
}

Application::~Application() {
	for (std::vector<Module*>::iterator it = modules.begin(); it != modules.end(); ++it) {
		delete* it;
	}
}

bool Application::Init() {
	bool ret = true;

	for (std::vector<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

UpdateStatus Application::Update() {
	unsigned int current_time = SDL_GetTicks();
	delta_time = (current_time - last_time) / 1000.0f;
	last_time = current_time;

	UpdateStatus ret = UpdateStatus::kUpdateContinue;

	for (std::vector<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UpdateStatus::kUpdateContinue; ++it)
		ret = (*it)->PreUpdate();

	for (std::vector<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UpdateStatus::kUpdateContinue; ++it)
		ret = (*it)->Update();

	for (std::vector<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UpdateStatus::kUpdateContinue; ++it)
		ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp() {
	bool ret = true;

	for (std::vector<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}

void Application::RequestBrowser(const char* url) {
	ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}