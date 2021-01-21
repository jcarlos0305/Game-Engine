#include "UI/MainMenu.h"
#include "UI/About.h"
#include "UI/Console.h"

#include "Main/Application.h"
#include "Modules/ModuleEditor.h"
#include "Modules/ModuleScene.h"
#include "Modules/ModuleCamera.h"

#include "ImGui/imgui.h"

UpdateStatus MainMenu::Draw() {
	UpdateStatus ret = UpdateStatus::kUpdateContinue;

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Save")) {
				App->scene->ToJSON();
			}

			if (ImGui::MenuItem("Load")) {
				App->scene->FromJSON();
				// App->scene->InitializeQuadtree();
			}

			if (ImGui::MenuItem("Exit")) {
				ret = UpdateStatus::kUpdateStop;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View")) {
			for (UIWindow* window : App->editor->windows) {
				if (window->title != "About") {
					if (ImGui::MenuItem(window->title, NULL, window->visible)) {
						window->Show((bool*)!window->visible);
					}
				}
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("GameObject")) {
			if (ImGui::MenuItem("Camera")) {
				App->camera->CreateCameraGameObject();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("Github")) {
				App->RequestBrowser(REPO_URL);
			}
			if (ImGui::MenuItem("About")) {
				bool show = true;
				App->editor->about->Show(&show);
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	return ret;
}