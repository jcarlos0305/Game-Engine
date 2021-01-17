#include "Main/Application.h"
#include "Modules/ModuleRender.h"
#include "Debug Draw/ModuleDebugDraw.h"
#include "ModuleScene.h"
#include "ModuleCamera.h"

#include "Components/ComponentMesh.h"
#include "Components/ComponentTransform.h"

typedef math::float3 ddVec3;

ModuleScene::ModuleScene() : root(new GameObject()) {
	root->SetName("root");
	root->AddComponent(new ComponentTransform());
	quadtree = new Quadtree(AABB(float3(-50,-50,-50),float3(50,50,50)));
}

ModuleScene::~ModuleScene() {}

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