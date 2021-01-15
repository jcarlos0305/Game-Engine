#include "GameObject.h"
#include "Components/ComponentTransform.h"
#include "Components/ComponentMesh.h"
#include "Utils/Utils.h"
#include "Utils/UUID.h"

GameObject::GameObject() : UUID(custom_UUID::generate()) {}

GameObject::GameObject(const char* _uuid, const char* _name) : UUID(_uuid), name(_strdup(_name)) {}

GameObject::GameObject(Json::Value& _game_object_data) {
	FromJson(_game_object_data);
}

GameObject::~GameObject() {
	free(name);
	name = nullptr;
	for (Component* component : components) delete component;
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
	_root[name][JSON_PROPERTY_GAME_OBJECT_NAME] = name;
	_root[name][JSON_PROPERTY_GAME_OBJECT_UUID] = UUID;
	_root[name][JSON_PROPERTY_GAME_OBJECT_PARENT_UUID] = parent ? parent->GetUUID() : "NULL";

	Json::Value component_array_root(Json::arrayValue);
	Json::Value children_root;

	for (Component* component : components) {
		component->ToJson(component_array_root);
	};
	_root[name][JSON_PROPERTY_GAME_OBJECT_COMPONENTS] = component_array_root;

	for (GameObject* child : children) {
		child->ToJson(children_root, child);
	};
	_root[name][JSON_PROPERTY_GAME_OBJECT_CHILDREN] = children_root;
}

void GameObject::FromJson(Json::Value& _game_object_data) {
	//for (Json::Value json_content : _game_object_data) {
	//	name = _strdup(json_content[JSON_PROPERTY_GAME_OBJECT_NAME].asCString());
	//	UUID = _game_object_data[0][JSON_PROPERTY_GAME_OBJECT_UUID].asCString();
	//}

	name = _strdup(_game_object_data[JSON_PROPERTY_GAME_OBJECT_NAME].asCString());
	UUID = _game_object_data[JSON_PROPERTY_GAME_OBJECT_UUID].asCString();

	for (Json::Value game_object_json : _game_object_data[JSON_PROPERTY_GAME_OBJECT_CHILDREN]) {
		GameObject* child = new GameObject(game_object_json);
		child->SetParent(this);
		AddChild(child);
	}

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
	}

	//for (Json::Value::ArrayIndex i = 0; i != _root[0][JSON_PROPERTY_GAME_OBJECT_COMPONENTS].size(); i++) {
	//	//_root[name][JSON_PROPERTY_GAME_OBJECT_COMPONENTS][i]
	//	//if
	//}

	/*for (Component* component : components) {
		component->ToJSON(components_root);
	};
	_root[name][JSON_PROPERTY_GAME_OBJECT_COMPONENTS] = components_root;

	for (GameObject* child : children) {
		child->ToJson(children_root, child);
	};
	_root[name][JSON_PROPERTY_GAME_OBJECT_CHILDREN] = children_root;*/
}