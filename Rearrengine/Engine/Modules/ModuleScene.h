#pragma once

#include "Module.h"

#include "Resources/GameObject.h"

class ModuleScene : public Module {
public:
	ModuleScene();
	~ModuleScene();

	inline GameObject* GetRoot() { return root; };
	GameObject* InitializeRoot();
	void Draw(GameObject& game_object);

	void RecursiveDelete(GameObject* game_object);

	bool CleanUp();

	void ToJSON() const override;
	void FromJSON() override;

private:
	GameObject* root = nullptr;
};