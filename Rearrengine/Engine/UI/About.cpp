#include "About.h"

#include "ImGui/imgui.h"

About::About() {
	visible = false;
	title = "About";
}

About::~About() {}

void About::Draw() {
	ImGui::Begin(title, &visible, ImGuiWindowFlags_NoCollapse);

	// Engine name
	ImGui::Text("Rearengine v.");
	ImGui::SameLine();
	ImGui::Text(ENGINE_VERSION);

	// Description
	ImGui::Text("3D Engine developed for learning purposes");

	// Team
	ImGui::Text("Authors: ");
	//ImGui::SameLine();
	ImGui::Text(DEVELOPER);
	ImGui::Text(DEVELOPER_2);

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