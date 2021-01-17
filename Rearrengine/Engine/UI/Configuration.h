#pragma once

#include "Utils/Globals.h"
#include "Resources/GameObject.h"
#include "UIWindow.h"
#include "Components/ComponentTransform.h"

#include "Math/float3.h"

class Configuration : public UIWindow {
public:
	Configuration();
	~Configuration();

	inline void SetSelectedGameObject(GameObject* _game_object) { selected_game_object = _game_object; };
	inline GameObject* GetSelectedGameObject() const { return selected_game_object; };

	void Draw();

	bool CleanUp();

private:
	void DrawModifiableVector(float3& vector, ComponentTransform* transform, int type);

private:
	GameObject* selected_game_object = nullptr;
};