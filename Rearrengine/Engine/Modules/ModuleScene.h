#pragma once

#include "Module.h"

#include "Resources/GameObject.h"
#include "Resources/Quadtree.h"

class ModuleScene : public Module {
public:
	ModuleScene();
	~ModuleScene();

	inline GameObject* GetRoot() { return root; };
	void Draw(GameObject& game_object);

	void RecursiveDelete(GameObject* game_object);

	UpdateStatus Update() override;
	bool CleanUp();

private:
	GameObject* root = nullptr;
	Quadtree* quadtree = nullptr;
};