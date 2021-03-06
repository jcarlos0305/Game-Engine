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
	ImGui::Begin(title, &visible, ImGuiWindowFlags_NoCollapse);
	if (App->scene->GetRoot()) {
		DrawRecursive(*App->scene->GetRoot());
	}
	ImGui::End();
}

void Hierarchy::DrawRecursive(GameObject& game_object) {
	std::vector<GameObject*> children = game_object.GetChildren();
	for (unsigned int i = 0; i < game_object.GetChildrenCount(); i++) {
		char GameObjectID[_MAX_DIR];
		sprintf_s(GameObjectID, "%s##%s", children[i]->GetName(), children[i]->GetUUID().c_str());
		if (children[i]->GetChildrenCount() == 0) {
			if (ImGui::Selectable(GameObjectID, App->editor->configuration->GetSelectedGameObject() == children[i])) {
				App->editor->configuration->SetSelectedGameObject(children[i]);
			}
		}
		else {
			ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
			if (App->editor->configuration->GetSelectedGameObject() == children[i]) node_flags |= ImGuiTreeNodeFlags_Selected;

			if (ImGui::TreeNodeEx(GameObjectID, node_flags)) {
				if (ImGui::IsItemClicked()) App->editor->configuration->SetSelectedGameObject(children[i]);
				DrawRecursive(*children[i]);
				ImGui::TreePop();
			}
		}
	}
}