#pragma once

#include "Utils/Globals.h"
#include "Components/Component.h"
#include "Math/float4x4.h"

#include <vector>

class GameObject {
public:
	GameObject();
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

private:
	char* name = "";
	std::vector<GameObject*> children;
	std::vector<Component*>  components;

	GameObject* parent = nullptr;
};