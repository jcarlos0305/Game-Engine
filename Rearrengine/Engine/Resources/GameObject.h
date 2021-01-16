#pragma once

#include "Utils/Globals.h"
#include "Components/Component.h"
#include "Math/float4x4.h"

#include <json/json.h>
#include <string>
#include <vector>

class GameObject {
public:
	GameObject();
	GameObject(const char* _uuid, const char* _name);
	GameObject(Json::Value& _game_object_data);
	~GameObject();

	void SetName(const char* _name) { name = _strdup(_name); };
	const char* GetName() const { return name; };

	void AddChild(GameObject* _child) { children.push_back(_child); };
	void AddComponent(Component* _component) { components.push_back(_component); };

	inline std::vector<GameObject*> GetChildren() const { return children; };
	inline int GetChildrenCount() const { return children.size(); };

	inline std::vector<Component*>  GetComponents() const { return components; };
	inline int GetComponentCount() const { return components.size(); };

	bool HasComponentType(ComponentTypes _type) const;
	Component* GetComponentType(ComponentTypes _type) const;

	const float4x4 GameObject::GetGlobalMatrix() const;
	inline GameObject* GetParent() const { return parent; };
	inline void SetParent(GameObject* _parent) { parent = _parent; };
	void UpdateChildrenGlobalMatrix();

	void ToJson(Json::Value& _root, GameObject* _game_object);
	void FromJson(Json::Value& _game_object_data);

	std::string GetUUID() const { return UUID; };
	void SetUUID(const char* _uuid) { UUID = _uuid; };

private:
	std::string UUID;
	char* name = "";
	std::vector<GameObject*> children;
	std::vector<Component*>  components;

	GameObject* parent = nullptr;
};