#pragma once

#include "QuadtreeNode.h"
#include "Utils/Globals.h"

class Quadtree
{
public:
	Quadtree(const AABB aabb);
	~Quadtree();

	inline QuadtreeNode* GetRoot() { return root; };

	void InsertGameObject(GameObject* gameObject);

private:
	QuadtreeNode* root = nullptr;
};

