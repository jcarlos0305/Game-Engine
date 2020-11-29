#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleModel.h"
#include "ModuleCamera.h"

// UI
#include "MainMenu.h"
#include "Configuration.h"
#include "Console.h"
#include "About.h"
#include "Viewport.h"

#include <GL/glew.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"

#include "LeakTest.h"

ModuleEditor::ModuleEditor() {
	console = new Console();
}

ModuleEditor::~ModuleEditor() {
	for (UiComponent* window : windows) delete window;
}

bool ModuleEditor::Init() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->render->context);
	ImGui_ImplOpenGL3_Init();

	windows.push_back(console);
	windows.push_back(configuration = new Configuration());
	windows.push_back(about = new About());
	windows.push_back(viewport = new Viewport());

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_DockingEnable;
	io.ConfigWindowsMoveFromTitleBarOnly;
	io.ConfigWindowsMoveFromTitleBarOnly = true;

	return true;
}

UpdateStatus ModuleEditor::PreUpdate() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();
	return UpdateStatus::kUpdateContinue;
}

UpdateStatus ModuleEditor::Update() {
	// Menu bar
	UpdateStatus ret = MainMenu::Draw();

	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	// Rendering the windows
	for (UiComponent* window : windows)
		if (window->visible) window->Draw();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	return ret;
}

UpdateStatus ModuleEditor::PostUpdate() {
	return UpdateStatus::kUpdateContinue;
}

void ModuleEditor::AddLog(const char* log) {
	console->AddLog(log);
}

bool ModuleEditor::CleanUp() {
	for (UiComponent* window : windows) window->CleanUp();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return true;
}