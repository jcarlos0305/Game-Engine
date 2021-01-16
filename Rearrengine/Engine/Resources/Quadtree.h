#pragma once

#include "QuadtreeNode.h"
#include "Utils/Globals.h"

class Quadtree
{
public:
	Quadtree(const AABB aabb);
	~Quadtree();

	void Draw();

private:
	QuadtreeNode* root = nullptr;
	int depth = DEPTH_QUADTREE;
};

