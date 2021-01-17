#pragma once

#include <Geometry/AABB.h>
#include <Geometry/OBB.h>
#include <Resources/GameObject.h>

class QuadtreeNode
{
public:
	QuadtreeNode(const AABB aabb);
	QuadtreeNode(const AABB aabb, QuadtreeNode* _parent, int _index);
	~QuadtreeNode();

	inline AABB GetBoundingBox() { return boundingBox; };

	void Draw();

	void CreateChildrenNodes();
	inline std::vector<QuadtreeNode*> GetChildren() { return children; };

	inline std::vector<GameObject*> GetGameObjects() { return gameObjects; };
	void InsertGameObject(GameObject* gameObject);

	inline int GetIndex() { return index; };

private:
	AABB boundingBox;

	QuadtreeNode* parent = nullptr;
	// [0] NW - [1] NE - [2] SW - [3] SE 
	std::vector<QuadtreeNode*> children;
	std::vector<GameObject*> gameObjects;

	int index;
	bool isDivided;
};

