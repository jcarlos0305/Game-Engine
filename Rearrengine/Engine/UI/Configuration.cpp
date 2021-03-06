#include "UI/Configuration.h"
#include "Main/Application.h"
#include "Modules/ModuleCamera.h"
#include "Modules/ModuleModel.h"
#include "Modules/ModuleScene.h"

#include "Components/ComponentMesh.h"
#include "Resources/Mesh.h"
#include <vector>

#include "ImGui/imgui.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"

#include "Math/float3x3.h"
#include "Math/float3x4.h"
#include "Math/float4x4.h"

static float3 translate_vector;
static float3 rotation_vector;
static float3 scale_vector;

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
		float3 camera_position = App->camera->GetPosition();
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

	if (selected_game_object) {
		if (ImGui::CollapsingHeader("Transform")) {
			ImGui::Text(selected_game_object->GetName());
			ImGui::Columns(4, NULL, false);
			ImGui::Text("    x    "); ImGui::NextColumn();
			ImGui::Text("    y    "); ImGui::NextColumn();
			ImGui::Text("    z    "); ImGui::NextColumn();
			ImGui::Text("         "); ImGui::NextColumn();

			ComponentTransform* component_transform = static_cast<ComponentTransform*>(selected_game_object->GetComponentType(ComponentTypes::kTransform));

			// Position
			translate_vector = component_transform->GetTranslate();
			DrawModifiableVector(translate_vector, component_transform, 0);
			ImGui::Text("Position"); ImGui::NextColumn();
			ImGui::Separator();

			// Scale
			scale_vector = component_transform->GetScale();
			DrawModifiableVector(scale_vector, component_transform, 1);
			ImGui::Text("Scale");  ImGui::NextColumn();
			ImGui::Separator();

			// Rotaton
			rotation_vector = component_transform->GetRotation();
			DrawModifiableVector(rotation_vector, component_transform, 2);
			ImGui::Text("Rotation");  ImGui::NextColumn();

			ImGui::Columns(1);
			ImGui::NewLine();
		}

		ComponentMesh* component_mesh = static_cast<ComponentMesh*>(selected_game_object->GetComponentType(ComponentTypes::kMesh));
		if (component_mesh) {
			if (ImGui::CollapsingHeader("Geometry")) {
				ImGui::Text(selected_game_object->GetName());
				Mesh* mesh = component_mesh->GetMesh();
				ImGui::Text("Vertices: %u", mesh->num_vertices, 0);
				ImGui::Text("Triangles: %u", mesh->num_faces, 0);
				ImGui::NewLine();
			}
		}
	}

	if (ImGui::CollapsingHeader("Texture")) {
		for (unsigned int i = 0; i < App->model->textures.size(); i++) {
			ImGui::Image((ImTextureID)App->model->textures[i], ImVec2(128, 128));
		}
	}
	ImGui::End();
}

void Configuration::DrawModifiableVector(float3& vector, ComponentTransform* transform, int type) {
	for (unsigned int i = 0; i < 3; i++) {
		ImGui::PushID(&vector[i]);
		if (ImGui::DragFloat("", &vector[i], 1.0f, -FLT_MAX, +FLT_MAX, "%.4f", ImGuiSliderFlags_None)) {
			transform->SetTransform(translate_vector, rotation_vector, scale_vector);
			selected_game_object->UpdateChildrenGlobalMatrix();
			if (type == 1) {
				ComponentMesh* component_mesh = static_cast<ComponentMesh*>(selected_game_object->GetComponentType(ComponentTypes::kMesh));
				if (component_mesh) App->model->UpdateMinMax(vector, component_mesh->GetMesh());
			}
		}
		ImGui::PopID();
		ImGui::NextColumn();
	}
}

bool Configuration::CleanUp() {
	return true;
}