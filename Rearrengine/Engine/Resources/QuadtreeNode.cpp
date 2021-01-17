#include "QuadtreeNode.h"
#include "Main/Application.h"
#include "Utils/Globals.h"
#include "Debug Draw/ModuleDebugDraw.h"

QuadtreeNode::QuadtreeNode(const AABB aabb)
{
	boundingBox = aabb;
	index = 0;
	isDivided = false;
}

QuadtreeNode::QuadtreeNode(const AABB aabb, QuadtreeNode* _parent, int _index)
{
	boundingBox = aabb;
	index = _index;
	parent = _parent;
	isDivided = false;
}

QuadtreeNode::~QuadtreeNode()
{
	for (QuadtreeNode* child : GetChildren()) {
		if (child != nullptr) {
			delete child;
			child = nullptr;
		}
	}
}

void QuadtreeNode::Draw()
{
	App->debug_draw->DrawAABB(float3(boundingBox.MaxX(), boundingBox.MaxY(), boundingBox.MaxZ()), 
		float3(boundingBox.MinX(), boundingBox.MinY(), boundingBox.MinZ()), float3(0.941176f, 0.972549f, 1.000000f));
}

void QuadtreeNode::CreateChildrenNodes()
{
	AABB childNode;

	float3 center = boundingBox.CenterPoint();
	float3 childCenter;

	float3 size = boundingBox.Size();
	float3 childSize = float3(size.x / 2, size.y, size.z / 2);

	int childIndex = index+1;

	// NW
	childCenter.x = center.x - size.x / 4;
	childCenter.y = center.y;
	childCenter.z = center.z + size.z / 4;
	childNode.SetFromCenterAndSize(childCenter, childSize);
	children.push_back(new QuadtreeNode(childNode, this, childIndex));
	// NE
	childCenter.x = center.x + size.x / 4;
	childCenter.y = center.y;
	childCenter.z = center.z + size.z / 4;
	childNode.SetFromCenterAndSize(childCenter, childSize);
	children.push_back(new QuadtreeNode(childNode, this, childIndex));
	// SW
	childCenter.x = center.x - size.x / 4;
	childCenter.y = center.y;
	childCenter.z = center.z - size.z / 4;
	childNode.SetFromCenterAndSize(childCenter, childSize);
	children.push_back(new QuadtreeNode(childNode, this, childIndex));
	// SE
	childCenter.x = center.x + size.x / 4;
	childCenter.y = center.y;
	childCenter.z = center.z - size.z / 4;
	childNode.SetFromCenterAndSize(childCenter, childSize);
	children.push_back(new QuadtreeNode(childNode, this, childIndex));

	this->isDivided = true;
}

void QuadtreeNode::InsertGameObject(GameObject* gameObject)
{
	if (!isDivided) { // If the node is not divided -> insert and divided 
		gameObjects.push_back(gameObject);
		int limitDepth = DEPTH_QUADTREE;
		if (index < limitDepth) { // If reack the last possible level 
			CreateChildrenNodes();
		}
	}
	else { // Check in which leaf should be insert
		OBB boundingBoxGameObject = gameObject->GetOBB();
		for (QuadtreeNode* child : GetChildren()) {
			if (child->GetBoundingBox().Intersects(boundingBoxGameObject)) {
				child->InsertGameObject(gameObject);
			}
		}
	}
}

std::vector<GameObject*> QuadtreeNode::CheckMousePicking(QuadtreeNode* node, LineSegment ray)
{
	std::vector<GameObject*> hitGameObject;
	if (ray.Intersects(GetBoundingBox())) { // ray vs. AABB
		for (GameObject* gameObject : GetGameObjects()) {
			hitGameObject.push_back(gameObject);
		}
	}
	else {
		for (QuadtreeNode* child : GetChildren()) {
			CheckMousePicking(child, ray);
		}
	}
	return hitGameObject;
}

std::vector<GameObject*> QuadtreeNode::CheckMousePicking(LineSegment ray)
{
	std::vector<GameObject*> hitGameObject;
	if (ray.Intersects(GetBoundingBox())) { // ray vs. AABB
		for (GameObject* gameObject : GetGameObjects()) {
			hitGameObject.push_back(gameObject);
		}
	}
	else {
		for (QuadtreeNode* child : GetChildren()) {
			CheckMousePicking(child, ray);
		}
	}
	return hitGameObject;
}


