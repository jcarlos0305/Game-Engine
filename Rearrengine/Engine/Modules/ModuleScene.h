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
	inline Quadtree* GetQuadtree() { return quadtree; };
	void Draw(QuadtreeNode* quadtreeNode);
	void Draw(GameObject& game_object);
	void DrawMesh(GameObject& game_object);
	void DrawQuadtree(QuadtreeNode* quadtreeNode);
	GameObject* InitializeRoot();

	void RecursiveDelete(GameObject* game_object);

	UpdateStatus Update() override;
	bool CleanUp();

	bool drawQuadtree = true;

	void ToJSON() const override;
	void FromJSON() override;

private:
	GameObject* root = nullptr;
	Quadtree* quadtree = nullptr;
};