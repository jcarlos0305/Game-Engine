#pragma once

#include <Geometry/AABB.h>
#include <Geometry/OBB.h>
#include "../MathGeoLib/Geometry/LineSegment.h"
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
	std::vector<GameObject*> CheckMousePicking(QuadtreeNode* node, LineSegment ray);
	std::vector<GameObject*> CheckMousePicking(LineSegment ray);

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

