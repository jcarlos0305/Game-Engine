#include "ModuleScene.h"

#include "Components/ComponentMesh.h"
#include "Components/ComponentTransform.h"

#include "Main/Application.h"
#include "Modules/ModuleModel.h"

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
	if (game_object) {
		for (GameObject* child : game_object->GetChildren()) {
			RecursiveDelete(child);
		}
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
	Json::Value textures_root;

	std::string path = JSON_ROOT_PATH;
	std::string extension = JSON_FILE_EXTENSION;

	std::string scene(path + "scene" + extension);
	std::string textures(path + JSON_TEXTURES_DIRECTORY + "textures" + extension);

	LoadFromFile(scene, scene_root);
	LoadFromFile(textures, textures_root);

	App->model->LoadTexturesFromJson(textures_root);
	root = new GameObject(scene_root[0]["root"]);
}