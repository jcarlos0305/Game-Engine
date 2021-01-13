#include "Main/Application.h"
#include "Modules/ModuleRender.h"
#include "Debug Draw/ModuleDebugDraw.h"
#include "ModuleScene.h"
#include "ModuleCamera.h"

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
		// If we have at least one GameObject Camera
		if (App->camera->GetGameCamera()) {
			// Object by object -> IMPROVE
			bool isMeshInsideFrustum = App->camera->GetGameCamera()->GetFrustum().Intersects(game_object.GetAABB());
			if (isMeshInsideFrustum) {
				// Drawing quads from mesh to check its hitbox
				if (App->render->showQuad) App->debug_draw->DrawQuad(float3(game_object.GetAABB().MaxX(), game_object.GetAABB().MaxY(), game_object.GetAABB().MaxZ()), float3(game_object.GetAABB().MinX(), game_object.GetAABB().MinY(), game_object.GetAABB().MinZ()));
				component_mesh->Draw();
			}
		}
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