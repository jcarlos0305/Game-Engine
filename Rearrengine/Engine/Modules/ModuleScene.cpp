#include "ModuleScene.h"

#include "Components/ComponentMesh.h"
#include "Components/ComponentTransform.h"

#include "Utils/Utils.h"

ModuleScene::ModuleScene() {}

ModuleScene::~ModuleScene() {}

GameObject* ModuleScene::InitializeRoot() {
	root = new GameObject();
	root->SetName("root");
	root->AddComponent(new ComponentTransform());
	return root;
}

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

void ModuleScene::ToJSON() const {
	Json::Value scene_root;
	root->ToJson(scene_root, root);
	PrintToFile("scene", "", scene_root);
}

void ModuleScene::FromJSON() {
	Json::Value scene_root;
	std::string path = JSON_ROOT_PATH;
	std::string extension = JSON_FILE_EXTENSION;
	path.append("scene" + extension);
	LoadFromFile(path, scene_root);
	//root = new GameObject(scene_root["root"][JSON_PROPERTY_GAME_OBJECT_UUID].asCString(), scene_root["root"][JSON_PROPERTY_GAME_OBJECT_NAME].asCString());
	root = new GameObject(scene_root["root"]);
	//root->FromJson();
}