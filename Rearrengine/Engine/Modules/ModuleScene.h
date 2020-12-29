#pragma once

#include "Module.h"

#include "../Resources/GameObject.h"

class ModuleScene : public Module {
public:
	ModuleScene();
	~ModuleScene();

	inline GameObject* GetRoot() { return root; };
	void Draw(GameObject& game_object);

private:
	GameObject* root = nullptr;
};