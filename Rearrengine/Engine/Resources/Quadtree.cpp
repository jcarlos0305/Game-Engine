#include "Quadtree.h"

Quadtree::Quadtree(const AABB aabb)
{
	root = new QuadtreeNode(aabb);
}

Quadtree::~Quadtree()
{
	// release quadtree node
}

void Quadtree::InsertGameObject(GameObject* gameObject)
{
	if (root != nullptr) {
		if (gameObject->GetAABB().Intersects(root->GetBoundingBox())) {
			root->InsertGameObject(gameObject);
		}
	}
}
