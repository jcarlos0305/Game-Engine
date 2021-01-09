#include "ComponentMesh.h"

#include "Utils/Globals.h"
#include "Main/Application.h"
#include "Modules/ModuleModel.h"
#include "Resources/GameObject.h"

#include "Math/float4x4.h"

ComponentMesh::ComponentMesh() {
	type = ComponentTypes::kMesh;
}

ComponentMesh::~ComponentMesh() {
	delete mesh;
	mesh = nullptr;
}

void ComponentMesh::Draw() const {
	mesh->Draw(App->model->textures, game_object->GetGlobalMatrix());
};