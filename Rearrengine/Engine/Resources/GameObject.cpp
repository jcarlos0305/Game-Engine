#include "GameObject.h"
#include "Components/ComponentTransform.h"
#include "Components/ComponentMesh.h"
#include "Utils/Utils.h"
#include "Utils/UUID.h"

#include "Main/Application.h"
#include "Modules/ModuleRender.h"
#include "Debug Draw/ModuleDebugDraw.h"
#include "Components/ComponentMesh.h"

GameObject::GameObject() : UUID(custom_UUID::generate()) {}

GameObject::GameObject(const char* _uuid, const char* _name) : UUID(_uuid), name(_strdup(_name)) {}

GameObject::GameObject(Json::Value& _game_object_data) {
	FromJson(_game_object_data);
}

GameObject::~GameObject() {
	free(name);
	name = nullptr;
	for (Component* component : components) delete component; // ?
}

void GameObject::AddComponent(Component* _component)
{
	// Create GameObject's AABB if the component is a Mesh
	if (_component->GetType() == ComponentTypes::kMesh) {
		ComponentMesh* component_mesh = static_cast<ComponentMesh*>(_component);
		// Gets the AABB from Max-Min Mesh's Vertex
		float3 mins = float3(component_mesh->GetMinsVertex().x, component_mesh->GetMinsVertex().y, component_mesh->GetMinsVertex().z);
		float3 maxs = float3(component_mesh->GetMaxsVertex().x, component_mesh->GetMaxsVertex().y, component_mesh->GetMaxsVertex().z);
		aabb = AABB(mins, maxs);
		obb = aabb.Transform(GetGlobalMatrix());
	}
	// Save the component
	components.push_back(_component);
}

bool GameObject::HasComponentType(ComponentTypes _type) const {
	for (Component* component : components) {
		if (component->GetType() == _type) return true;
	}
	return false;
}

Component* GameObject::GetComponentType(ComponentTypes _type) const {
	for (Component* component : components) {
		if (component->GetType() == _type) return component;
	}
	return nullptr;
}

const float4x4 GameObject::GetGlobalMatrix() const {
	ComponentTransform* transform = static_cast<ComponentTransform*>(GetComponentType(ComponentTypes::kTransform));
	return transform->GetGlobalMatrix();
}

void GameObject::UpdateChildrenGlobalMatrix() {
	for (GameObject* child : children) {
		ComponentTransform* transform = static_cast<ComponentTransform*>(child->GetComponentType(ComponentTypes::kTransform));
		transform->UpdateGlobalMatrix();
	}
}

void GameObject::ToJson(Json::Value& _root, GameObject* _game_object) {
	std::string JSON_PROPERTY_GAME_OBJECT_ID = name;
	if (parent) JSON_PROPERTY_GAME_OBJECT_ID.append(" - " + UUID);

	Json::Value child_data;
	child_data[JSON_PROPERTY_GAME_OBJECT_ID][JSON_PROPERTY_GAME_OBJECT_NAME] = name;
	child_data[JSON_PROPERTY_GAME_OBJECT_ID][JSON_PROPERTY_GAME_OBJECT_UUID] = UUID;
	child_data[JSON_PROPERTY_GAME_OBJECT_ID][JSON_PROPERTY_GAME_OBJECT_PARENT_UUID] = parent ? parent->GetUUID() : "NULL";

	Json::Value component_array_root(Json::arrayValue);
	Json::Value children_array_root(Json::arrayValue);

	for (Component* component : components) {
		component->ToJson(component_array_root);
	};
	child_data[JSON_PROPERTY_GAME_OBJECT_ID][JSON_PROPERTY_GAME_OBJECT_COMPONENTS] = component_array_root;

	for (GameObject* child : children) {
		child->ToJson(children_array_root, child);
	};
	child_data[JSON_PROPERTY_GAME_OBJECT_ID][JSON_PROPERTY_GAME_OBJECT_CHILDREN] = children_array_root;
	_root.append(child_data);
}

void GameObject::FromJson(Json::Value& _game_object_data) {
	name = _strdup(_game_object_data[JSON_PROPERTY_GAME_OBJECT_NAME].asCString());
	UUID = _game_object_data[JSON_PROPERTY_GAME_OBJECT_UUID].asCString();

	for (Json::Value component_json : _game_object_data[JSON_PROPERTY_GAME_OBJECT_COMPONENTS]) {
		ComponentTypes type = (ComponentTypes)component_json[JSON_PROPERTY_TYPE].asInt();
		Component* component;
		switch (type) {
		case ComponentTypes::kTransform:
			component = new ComponentTransform(component_json, this);
			break;
		case ComponentTypes::kMesh:
			component = new ComponentMesh(component_json, this);
			break;
		default:
			break;
		}
		AddComponent(component);
	}

	for (Json::Value game_object_json : _game_object_data[JSON_PROPERTY_GAME_OBJECT_CHILDREN]) {
		std::string id = game_object_json.getMemberNames()[0];
		GameObject* child = new GameObject();
		child->SetParent(this);
		child->FromJson(game_object_json[id]);
		AddChild(child);
	}
}