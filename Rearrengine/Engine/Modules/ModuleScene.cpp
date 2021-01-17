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
	quadtree = new Quadtree(AABB(float3(-30,-30,-30),float3(30,30,30)));
}

ModuleScene::~ModuleScene() {}

void ModuleScene::Draw(GameObject& game_object) {
	if (game_object.HasComponentType(ComponentTypes::kMesh)) {
		ComponentMesh* component_mesh = static_cast<ComponentMesh*>(game_object.GetComponentType(ComponentTypes::kMesh));
		// If we have at least one GameObject Camera
		if (App->camera->GetGameCamera()) {
			// Object by object -> IMPROVE
			bool isMeshInsideFrustum = App->camera->GetGameCamera()->GetFrustum().Intersects(game_object.GetAABB());
			if (isMeshInsideFrustum) {
				// Drawing quads from mesh to check its hitbox - AABB
				//if (App->render->showQuad) App->debug_draw->DrawAABB(float3(game_object.GetAABB().MaxX(), game_object.GetAABB().MaxY(), game_object.GetAABB().MaxZ()), 
					//float3(game_object.GetAABB().MinX(), game_object.GetAABB().MinY(), game_object.GetAABB().MinZ()), float3(1.000000f, 0.411765f, 0.705882f));
				if (App->render->showQuad) App->debug_draw->DrawOBB(game_object.GetOBB(), float3(0.372549f, 0.619608f, 0.627451f));
				component_mesh->Draw();
			}
		}
	}

	for (GameObject* child : game_object.GetChildren()) {
		Draw(*child);
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