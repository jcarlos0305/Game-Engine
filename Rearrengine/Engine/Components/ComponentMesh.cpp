#include "ComponentMesh.h"

#include "Utils/Globals.h"
#include "Main/Application.h"
#include "Modules/ModuleModel.h"
#include "Resources/GameObject.h"

#include "Math/float4x4.h"

ComponentMesh::ComponentMesh() {
	type = ComponentTypes::kMesh;
}

ComponentMesh::ComponentMesh(Json::Value& _component_mesh_data, GameObject* _game_object) {
	FromJson(_component_mesh_data);
	SetOwner(_game_object);
}

ComponentMesh::~ComponentMesh() {
	delete mesh;
	mesh = nullptr;
}

void ComponentMesh::Draw() const {
	mesh->Draw(App->model->textures, game_object->GetGlobalMatrix());
}

void ComponentMesh::FromJson(Json::Value& _component_data) {
	mesh = new Mesh(_component_data[JSON_PROPERTY_COMPONENT_MESH_PATH].asCString());
}

void ComponentMesh::ToJson(Json::Value& _owner_root) const {
	std::stringstream path;
	path << JSON_ROOT_PATH << JSON_MESH_DIRECTORY << mesh->GetName() << JSON_FILE_EXTENSION;
	Json::Value component_mesh_root;
	component_mesh_root[JSON_PROPERTY_COMPONENT_MESH_PATH] = path.str();
	component_mesh_root[JSON_PROPERTY_TYPE] = (int)type;
	component_mesh_root[JSON_PROPERTY_NAME] = mesh->GetName();
	_owner_root.append(component_mesh_root);
	//_owner_root[JSON_PROPERTY_COMPONENT_MESH][JSON_PROPERTY_COMPONENT_MESH_PATH] = path.str();
};