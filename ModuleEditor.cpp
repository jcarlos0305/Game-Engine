#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleModel.h"

// UI
#include "MainMenu.h"
#include "Configuration.h"

#include <GL/glew.h>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"

#include "LeakTest.h"

bool ModuleEditor::Init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->render->context);
    ImGui_ImplOpenGL3_Init();
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

    // Configuration
    Configuration::Draw();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return ret;
}

UpdateStatus ModuleEditor::PostUpdate() {
    return UpdateStatus::kUpdateContinue;
}

bool ModuleEditor::CleanUp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    return true;
}