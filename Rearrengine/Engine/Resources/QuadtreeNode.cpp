#include "QuadtreeNode.h"
#include "Main/Application.h"
#include "Utils/Globals.h"
#include "Debug Draw/ModuleDebugDraw.h"

QuadtreeNode::QuadtreeNode(const AABB aabb)
{
	boundingBox = aabb;
	index = 0;
	isDivided = false;
	int depth = DEPTH_QUADTREE;
	if (index < depth) {
		CreateChildrenNodes();
	}
	InsertIntersectGameObjects();
}

QuadtreeNode::QuadtreeNode(const AABB aabb, QuadtreeNode* _parent, int _index)
{
	boundingBox = aabb;
	index = _index;
	parent = _parent;
	int depth = DEPTH_QUADTREE;
	if (index < depth) {
		CreateChildrenNodes();
	}
	InsertIntersectGameObjects();
}

QuadtreeNode::~QuadtreeNode()
{
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

void QuadtreeNode::InsertIntersectGameObjects()
{
}
