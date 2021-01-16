#include "Quadtree.h"

Quadtree::Quadtree(const AABB aabb)
{
	root = new QuadtreeNode(aabb);
}

Quadtree::~Quadtree()
{
	// release quadtree node
}

void Quadtree::Draw()
{
	root->Draw();
}
