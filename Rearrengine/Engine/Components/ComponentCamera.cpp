#include "Main/Application.h"
#include "ComponentCamera.h"
#include "Utils/UUID.h"

ComponentCamera::ComponentCamera()
{
	type = ComponentTypes::kCamera;
	camera = new Camera();
}

ComponentCamera::ComponentCamera(Json::Value& _component_camera, GameObject* _game_object)
{
	type = ComponentTypes::kTransform;
	SetOwner(_game_object);
	FromJson(_component_camera);
}

ComponentCamera::~ComponentCamera()
{
	delete camera;
	camera = nullptr;
}

void ComponentCamera::FromJson(Json::Value& _component_data) {
	//mesh = new Mesh(_component_data[JSON_PROPERTY_COMPONENT_MESH_PATH].asCString());
}

void ComponentCamera::ToJson(Json::Value& _owner_root) const {
	/*std::stringstream path;
	path << JSON_ROOT_PATH << JSON_MESH_DIRECTORY << mesh->GetName() << JSON_FILE_EXTENSION;
	Json::Value component_mesh_root;
	component_mesh_root[JSON_PROPERTY_COMPONENT_MESH_PATH] = path.str();
	component_mesh_root[JSON_PROPERTY_TYPE] = (int)type;
	component_mesh_root[JSON_PROPERTY_NAME] = mesh->GetName();
	_owner_root.append(component_mesh_root);
	//_owner_root[JSON_PROPERTY_COMPONENT_MESH][JSON_PROPERTY_COMPONENT_MESH_PATH] = path.str();*/
};