#include "Configuration.h"
#include "Application.h"
#include "ModuleCamera.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

#include "MathGeoLib/Math/float3.h"
#include "MathGeoLib/Math/float3x4.h"

void Configuration::Draw() {
	bool active = true;
	ImGui::Begin("Configuration", &active, ImGuiWindowFlags_NoCollapse);

	if (ImGui::CollapsingHeader("Camera")) {
		// Column header
		ImGui::Columns(4, NULL, false);
		ImGui::Text("    x    "); ImGui::NextColumn();
		ImGui::Text("    y    "); ImGui::NextColumn();
		ImGui::Text("    z    "); ImGui::NextColumn();
		ImGui::Text("         "); ImGui::NextColumn();
		
		// Front
		float3 camera_front = App->camera->GetFront();
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::DragFloat("", &camera_front.x, 0.0f); ImGui::NextColumn();
		ImGui::DragFloat("", &camera_front.y, 0.0f); ImGui::NextColumn();
		ImGui::DragFloat("", &camera_front.z, 0.0f); ImGui::NextColumn();
		ImGui::Text("Front"); ImGui::NextColumn();

		// Up
		float3 camera_up = App->camera->GetUp();
		ImGui::DragFloat("", &camera_up.x, 0.0f); ImGui::NextColumn();
		ImGui::DragFloat("", &camera_up.y, 0.0f); ImGui::NextColumn();
		ImGui::DragFloat("", &camera_up.z, 0.0f); ImGui::NextColumn();
		ImGui::Text("Up"); ImGui::NextColumn();

		// World
		float3x4 camera_position = App->camera->GetWorldMatrix();
		ImGui::DragFloat("", &camera_position.x, 0.0f); ImGui::NextColumn();
		ImGui::DragFloat("", &camera_position.y, 0.0f); ImGui::NextColumn();
		ImGui::DragFloat("", &camera_position.z, 0.0f); ImGui::NextColumn();
		ImGui::Text("Position"); ImGui::NextColumn();

		ImGui::NewLine();

		// Near plane
		ImGui::Columns(2, NULL, false);

		float near_plane = App->camera->GetNearPlane();
		ImGui::DragFloat("", &near_plane, 0.0f); ImGui::NextColumn();
		ImGui::Text("Near Plane Distance"); ImGui::NextColumn();

		// Far plane
		float far_plane = App->camera->GetFarPlane();
		ImGui::DragFloat("", &far_plane, 0.0f); ImGui::NextColumn();
		ImGui::Text("Far Plane Distance"); ImGui::NextColumn();

		// Horizontal FOV
		float field_of_view = App->camera->GetHorizontalFOV();
		ImGui::DragFloat("", &field_of_view, 0.0f); ImGui::NextColumn();
		ImGui::Text("Field of View"); ImGui::NextColumn();

		// Aspect ratio
		float aspect_ratio = App->camera->GetAspectRatio();
		ImGui::DragFloat("", &aspect_ratio, 0.0f); ImGui::NextColumn();
		ImGui::Text("Aspect Ratio"); ImGui::NextColumn();
	}
	ImGui::End();
}
