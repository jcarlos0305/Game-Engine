#include "ModuleScene.h"

#include "Components/ComponentMesh.h"
#include "Components/ComponentTransform.h"

ModuleScene::ModuleScene() : root(new GameObject()) {
	root->SetName("root");
	root->AddComponent(new ComponentTransform());
}

ModuleScene::~ModuleScene() {}

void ModuleScene::Draw(GameObject& game_object) {
	if (game_object.HasComponentType(ComponentTypes::kMesh)) {
		ComponentMesh* component_mesh = static_cast<ComponentMesh*>(game_object.GetComponentType(ComponentTypes::kMesh));
		component_mesh->Draw();
	}

	for (GameObject* child : game_object.GetChildren()) {
		Draw(*child);
	}
}

void ModuleScene::RecursiveDelete(GameObject* game_object) {
	for (GameObject* child : game_object->GetChildren()) {
		RecursiveDelete(child);
	}
	delete game_object;
}

bool ModuleScene::CleanUp() {
	RecursiveDelete(root);
	root = nullptr;
	return true;
}