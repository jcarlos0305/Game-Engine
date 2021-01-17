#include "Main/Application.h"
#include "Modules/ModuleRender.h"
#include "Debug Draw/ModuleDebugDraw.h"
#include "ModuleScene.h"
#include "ModuleCamera.h"

#include "Components/ComponentMesh.h"
#include "Components/ComponentTransform.h"

#include "Utils/Utils.h"

ModuleScene::ModuleScene() {}

ModuleScene::~ModuleScene() {}

GameObject* ModuleScene::InitializeRoot() {
	root = new GameObject();
	root->SetName("root");
	root->AddComponent(new ComponentTransform());
	quadtree = new Quadtree(AABB(float3(-50, -50, -50), float3(50, 50, 50)));
	return root;
}

void ModuleScene::Draw(QuadtreeNode* node)
{
	if (App->camera->GetGameCamera()) {
		bool isNodeInsideFrustum = App->camera->GetGameCamera()->GetFrustum().Intersects(node->GetBoundingBox());
		if (isNodeInsideFrustum) {
			for (GameObject* gameObject : node->GetGameObjects())
			DrawMesh(*gameObject);
		}
	}

	for (QuadtreeNode* child : node->GetChildren()) {
		Draw(child);
	}
}

void ModuleScene::DrawMesh(GameObject& game_object) {
	if (game_object.HasComponentType(ComponentTypes::kMesh)) {
		ComponentMesh* component_mesh = static_cast<ComponentMesh*>(game_object.GetComponentType(ComponentTypes::kMesh));
		if (App->render->showQuad) App->debug_draw->DrawOBB(game_object.GetOBB(), float3(0.372549f, 0.619608f, 0.627451f));
		component_mesh->Draw();
	}
}


void ModuleScene::DrawQuadtree(QuadtreeNode* quadtreeNode)
{
	int depth = DEPTH_QUADTREE;
	if (quadtreeNode->GetIndex() < depth) {
		for (QuadtreeNode* child : quadtreeNode->GetChildren())
			DrawQuadtree(child);
	}
	quadtreeNode->Draw();

}

void ModuleScene::RecursiveDelete(GameObject* game_object) {
	for (GameObject* child : game_object->GetChildren()) {
		RecursiveDelete(child);
	}
	delete game_object;
}

UpdateStatus ModuleScene::Update()
{
	if (drawQuadtree) {
		DrawQuadtree(quadtree->GetRoot());
	}
	return UpdateStatus::kUpdateContinue;
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
	root = new GameObject(scene_root[0]["root"]);
}