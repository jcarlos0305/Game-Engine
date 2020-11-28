#include "About.h"

#include "ImGui/imgui.h"

About::About() {
	visible = false;
	title = "About";
}

About::~About() {}

void About::Draw() {
	ImGui::Begin("About", &visible, ImGuiWindowFlags_NoCollapse);

	// Engine name
	ImGui::Text("Rearengine v.");
	ImGui::SameLine();
	ImGui::Text(ENGINE_VERSION);

	// Description
	ImGui::Text("3D Engine developed for learning purposes");

	// Team
	ImGui::Text("Author: ");
	ImGui::SameLine();
	ImGui::Text(DEVELOPER);

	// Libraries
	ImGui::Text("Libraries");
	ImGui::SameLine();
	ImGui::Text("TBD");

	// License
	ImGui::Text(LICENCE);

	ImGui::End();
}

bool About::CleanUp() {
	return true;
}
