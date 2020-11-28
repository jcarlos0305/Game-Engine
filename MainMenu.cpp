#include "MainMenu.h"
#include "Application.h"
#include "About.h"
#include "ModuleEditor.h"
#include "Console.h"

#include "ImGui/imgui.h"

UpdateStatus MainMenu::Draw() {
	UpdateStatus ret = UpdateStatus::kUpdateContinue;

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Exit")) {
				ret = UpdateStatus::kUpdateStop;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View")) {
			for (UiComponent* window : App->editor->windows) {
				if (window->title != "About") {
					if (ImGui::MenuItem(window->title, NULL, window->visible)) {
						window->Show((bool*)!window->visible);
					}
				}
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