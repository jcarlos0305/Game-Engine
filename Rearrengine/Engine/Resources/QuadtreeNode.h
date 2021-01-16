#pragma once

#include <Geometry/AABB.h>
#include <Resources/GameObject.h>

class QuadtreeNode
{
public:
	QuadtreeNode(const AABB aabb);
	QuadtreeNode(const AABB aabb, QuadtreeNode* parent);
	~QuadtreeNode();

	void Draw();
	void insertGameObjects();

private:
	AABB boundingBox;

	QuadtreeNode* parent = nullptr;
	// [0] NW - [1] NE - [2] SW - [3] SE std::vector<QuadtreeNode*> children;
	QuadtreeNode* childNW = nullptr;
	QuadtreeNode* childNE = nullptr;
	QuadtreeNode* childSW = nullptr;
	QuadtreeNode* childSE = nullptr;
	std::vector<GameObject*> gameObjects;

	int index;
};

