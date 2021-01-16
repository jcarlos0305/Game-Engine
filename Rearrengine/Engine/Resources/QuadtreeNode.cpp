#include "QuadtreeNode.h"
#include "Main/Application.h"
#include "Debug Draw/ModuleDebugDraw.h"

QuadtreeNode::QuadtreeNode(const AABB aabb)
{
	boundingBox = aabb;
}

QuadtreeNode::QuadtreeNode(const AABB aabb, QuadtreeNode* parent)
{
	boundingBox = aabb;
	parent = parent;
}

QuadtreeNode::~QuadtreeNode()
{
}

void QuadtreeNode::Draw()
{
	App->debug_draw->DrawAABB(float3(boundingBox.MaxX(), boundingBox.MaxY(), boundingBox.MaxZ()), 
		float3(boundingBox.MinX(), boundingBox.MinY(), boundingBox.MinZ()), float3(0.941176f, 0.972549f, 1.000000f));
}

void QuadtreeNode::insertGameObjects()
{
}
