#include "UI/Configuration.h"
#include "Main/Application.h"
#include "Modules/ModuleCamera.h"
#include "Modules/ModuleModel.h"
#include "Modules/ModuleScene.h"

#include "Resources/Mesh.h"
#include <vector>

#include "ImGui/imgui.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

#include "Math/float3.h"
#include "Math/float3x3.h"
#include "Math/float3x4.h"
#include "Math/float4x4.h"

Configuration::Configuration() {
	title = "Configuration";
	visible = true;
}

Configuration::~Configuration() {}

void Configuration::Draw() {
	ImGui::Begin(title, &visible, ImGuiWindowFlags_NoCollapse);

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

		ImGui::PopItemFlag();
		ImGui::NewLine();

		// Near plane
		ImGui::Columns(2, NULL, false);

		float near_plane = App->camera->GetNearPlane();
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
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

		ImGui::PopItemFlag();
		ImGui::Columns(1);
	}

	if (ImGui::CollapsingHeader("Transform")) {
		ImGui::Columns(4, NULL, false);
		ImGui::Text("    x    "); ImGui::NextColumn();
		ImGui::Text("    y    "); ImGui::NextColumn();
		ImGui::Text("    z    "); ImGui::NextColumn();
		ImGui::Text("         "); ImGui::NextColumn();

		float4x4 model = App->model->model_matrix;
		// Position
		float3 position = model.TranslatePart();
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::DragFloat("", &position.x, 0.0f); ImGui::NextColumn();
		ImGui::DragFloat("", &position.y, 0.0f); ImGui::NextColumn();
		ImGui::DragFloat("", &position.z, 0.0f); ImGui::NextColumn();
		ImGui::Text("Position");                 ImGui::NextColumn();

		ImGui::Separator();

		// Scale
		float3 scale = model.GetScale();
		ImGui::DragFloat("", &scale.x, 0.0f); ImGui::NextColumn();
		ImGui::DragFloat("", &scale.y, 0.0f); ImGui::NextColumn();
		ImGui::DragFloat("", &scale.z, 0.0f); ImGui::NextColumn();
		ImGui::Text("Scale");                 ImGui::NextColumn();

		ImGui::Separator();

		// Rotaton
		float3x3 rotation = model.RotatePart();
		for (unsigned int i = 0; i < 3; i++) {
			for (unsigned int j = 0; j < 3; j++) {
				ImGui::DragFloat("", &rotation[i][j], 0.0f); ImGui::NextColumn();
			}
			if (i != 1) {
				ImGui::Text(""); ImGui::NextColumn();
			}
			else {
				ImGui::Text("Rotation"); ImGui::NextColumn();
			}
		}

		ImGui::PopItemFlag();
		ImGui::Columns(1);
		ImGui::NewLine();
	}

	if (ImGui::CollapsingHeader("Geometry")) {
		//std::vector<Mesh> meshes = App->model->meshes;
		std::vector<Mesh> meshes = App->scene->GetRoot();
		for (unsigned int i = 0; i < meshes.size(); i++) {
			ImGui::Text("Mesh %i", i);
			ImGui::Separator();
			ImGui::Text("Vertices: %u", meshes[i].num_vertices, 0);
			ImGui::Text("Triangles: %u", meshes[i].num_faces, 0);
			ImGui::NewLine();
		}
	}

	if (ImGui::CollapsingHeader("Texture")) {
		ImGui::Image((ImTextureID)App->model->textures[0], ImVec2(128, 128));
	}
	ImGui::End();
}

bool Configuration::CleanUp() {
	return true;
}