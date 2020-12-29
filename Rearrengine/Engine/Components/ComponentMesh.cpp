#include "ComponentMesh.h"

#include "../Utils/Globals.h"
#include "../Main/Application.h"
#include "../Modules/ModuleModel.h"

#include "Math/float4x4.h"

ComponentMesh::ComponentMesh() {
	type = ComponentTypes::kMesh;
}
void ComponentMesh::Draw() const {
	mesh->Draw(App->model->textures, float4x4::identity);
};
