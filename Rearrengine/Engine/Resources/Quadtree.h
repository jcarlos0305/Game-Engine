#pragma once

#include "QuadtreeNode.h"

class Quadtree
{
public:
	Quadtree();
	~Quadtree();

private:
	QuadtreeNode* root = nullptr;
	int depth = 3;
};

