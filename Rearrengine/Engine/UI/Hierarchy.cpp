#include "Hierarchy.h"

#include "Main/Application.h"
#include "Modules/ModuleScene.h"
#include "Modules/ModuleEditor.h"
#include "UI/Configuration.h"

#include "ImGui/imgui.h"

Hierarchy::Hierarchy() {
	title = "Hierarchy";
	visible = true;
}

Hierarchy::~Hierarchy() {}

void Hierarchy::Draw() {
	if (ImGui::Begin(title, &visible, ImGuiWindowFlags_NoCollapse)) {
		DrawRecursive(*App->scene->GetRoot());
		ImGui::End();
	}
}

void Hierarchy::DrawRecursive(GameObject& game_object) {
	std::vector<GameObject*> children = game_object.GetChildren();
	for (unsigned int i = 0; i < game_object.GetChildrenCount(); i++) {
		if (children[i]->GetChildrenCount() == 0) {
			if (ImGui::Selectable(children[i]->GetName())) {
				App->editor->configuration->SetSelectedGameObject(children[i]);
			}
		}
		else {
			if (ImGui::TreeNode(children[i]->GetName())) {
				DrawRecursive(*children[i]);
				ImGui::TreePop();
			}
			if (ImGui::IsItemClicked()) {
				App->editor->configuration->SetSelectedGameObject(children[i]);
			}
		}
	}
}