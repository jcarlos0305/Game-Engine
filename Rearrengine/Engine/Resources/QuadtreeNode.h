#pragma once

#include <Geometry/AABB.h>
#include <Resources/GameObject.h>

class QuadtreeNode
{
public:
	QuadtreeNode(const AABB aabb);
	QuadtreeNode(const AABB aabb, QuadtreeNode* _parent, int _index);
	~QuadtreeNode();

	void Draw();
	void CreateChildrenNodes();
	inline std::vector<QuadtreeNode*> GetChildren() { return children; };
	void InsertIntersectGameObjects();
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

