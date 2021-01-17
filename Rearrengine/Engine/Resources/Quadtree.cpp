#include "Quadtree.h"

Quadtree::Quadtree(const AABB aabb)
{
	root = new QuadtreeNode(aabb);
}

Quadtree::~Quadtree()
{
	delete root;
	root = nullptr;
}

void Quadtree::InsertGameObject(GameObject* gameObject)
{
	if (root != nullptr) {
		if (gameObject->GetOBB().Intersects(root->GetBoundingBox())) {
			root->InsertGameObject(gameObject);
		}
	}
}