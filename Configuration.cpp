#include "Configuration.h"
#include "Application.h"
#include "ModuleCamera.h"

#include "ImGui/imgui.h"
#include "MathGeoLib/Math/float3.h"
#include "MathGeoLib/Math/float3x4.h"

void Configuration::Draw() {
	bool active = true;
	ImGui::Begin("Configuration", &active, ImGuiWindowFlags_NoCollapse);

	if (ImGui::CollapsingHeader("Camera")) {
		// Column header
		ImGui::Columns(4);
		ImGui::Text("    x    "); ImGui::NextColumn();
		ImGui::Text("    y    "); ImGui::NextColumn();
		ImGui::Text("    z    "); ImGui::NextColumn();
		ImGui::Text("         "); ImGui::NextColumn();
		
		// Front
		float3 camera_front = App->camera->frustum.Front();
		ImGui::Text("%f", camera_front.x); ImGui::NextColumn();
		ImGui::Text("%f", camera_front.y); ImGui::NextColumn();
		ImGui::Text("%f", camera_front.z); ImGui::NextColumn();
		ImGui::Text("Front");              ImGui::NextColumn();
		ImGui::Separator();

		// Up
		float3 camera_up = App->camera->frustum.Up();
		ImGui::Columns(4);
		ImGui::Text("%f", camera_up.x); ImGui::NextColumn();
		ImGui::Text("%f", camera_up.y); ImGui::NextColumn();
		ImGui::Text("%f", camera_up.z); ImGui::NextColumn();
		ImGui::Text("Up");              ImGui::NextColumn();
		ImGui::Separator();

		// Position
		float3x4 camera_position = App->camera->frustum.WorldMatrix();
		ImGui::Columns(4);
		ImGui::Text("%f", camera_position.x); ImGui::NextColumn();
		ImGui::Text("%f", camera_position.y); ImGui::NextColumn();
		ImGui::Text("%f", camera_position.z); ImGui::NextColumn();
		ImGui::Text("Position");              ImGui::NextColumn();
	}
	ImGui::End();
}
