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

	for (UiComponent* window : windows)
		if (window->visible) window->Draw();

	RenderViewport();

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

void ModuleEditor::RenderViewport() {
	bool active = true;
	if (ImGui::Begin("Viewport", &active, ImGuiWindowFlags_NoCollapse)) {
		is_viewport_focused = ImGui::IsWindowFocused();
		
		static ImVec2 window_size = ImGui::GetWindowSize();

		App->render->RenderViewport(window_size.x, window_size.y);

		ImGui::GetWindowDrawList()->AddImage(
			(void*)(intptr_t)App->render->texture,
			ImGui::GetCursorScreenPos(),
			ImVec2(ImGui::GetCursorScreenPos().x + window_size.x, ImGui::GetCursorScreenPos().y + window_size.y),
			ImVec2(0, 1), ImVec2(1, 0)
		);

		ImVec2 new_window_size = ImGui::GetWindowSize();
		if (window_size.x != new_window_size.x || window_size.y != new_window_size.y) {
			App->camera->SetAspectRatio(new_window_size.x / new_window_size.y);
			window_size = ImGui::GetWindowSize();
		}
	}
	ImGui::End();
}

bool ModuleEditor::CleanUp() {
	for (UiComponent* window : windows) window->CleanUp();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return true;
}