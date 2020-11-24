#include "MainMenu.h"
#include "Application.h"
#include "About.h"

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
		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("Github")) {
				App->RequestBrowser(REPO_URL);
			}
			if (ImGui::MenuItem("About")) {
				About::Draw();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	return ret;
}