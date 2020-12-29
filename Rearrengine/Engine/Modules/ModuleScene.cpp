#include "ModuleScene.h"

#include "../Components/ComponentMesh.h"

ModuleScene::ModuleScene() : root(new GameObject()) {}

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
