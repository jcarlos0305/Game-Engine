#pragma once

#include "Module.h"

#include "Resources/GameObject.h"
#include "Resources/Quadtree.h"
#include "Resources/QuadtreeNode.h"

class ModuleScene : public Module {
public:
	ModuleScene();
	~ModuleScene();

	inline GameObject* GetRoot() { return root; };
	void Draw(GameObject& game_object);
	void DrawQuadtree(QuadtreeNode* quadtreeNode);

	void RecursiveDelete(GameObject* game_object);

	UpdateStatus Update() override;
	bool CleanUp();

	bool drawQuadtree = true;

private:
	GameObject* root = nullptr;
	Quadtree* quadtree = nullptr;
};