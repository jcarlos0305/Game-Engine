#pragma once

#include "Utils/Globals.h"
#include "Components/Component.h"
#include "Math/float4x4.h"

#include <json/json.h>
#include <string>
#include <vector>
#include <Geometry/AABB.h>
#include <Geometry/OBB.h>

class GameObject {
public:
	GameObject();
	GameObject(const char* _uuid, const char* _name);
	GameObject(Json::Value& _game_object_data);
	~GameObject();

	void SetName(const char* _name) { name = _strdup(_name); };
	const char* GetName() const { return name; };

	void AddChild(GameObject* _child) { children.push_back(_child); };
	void AddComponent(Component* _component);

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

	inline AABB GetAABB() { return aabb; }
	inline void SetAABB(AABB& _aabb) { aabb = _aabb; }
	inline OBB GetOBB() { return obb; } // Not do it yet transform with World Matrix
	inline void SetOBB(OBB& _obb) { obb = _obb; }

	void ToJson(Json::Value& _root, GameObject* _game_object);
	void FromJson(Json::Value& _game_object_data);

	std::string GetUUID() const { return UUID; };
	void SetUUID(const char* _uuid) { UUID = _uuid; };

private:
	std::string UUID;
	char* name = "";
	AABB aabb;
	OBB obb;
	std::vector<GameObject*> children;
	std::vector<Component*>  components;

	GameObject* parent = nullptr;
};