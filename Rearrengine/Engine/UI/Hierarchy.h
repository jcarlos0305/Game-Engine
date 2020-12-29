#pragma once

#include "UIWindow.h"
#include "../Resources/GameObject.h"

#include <vector>

class Hierarchy : public UIWindow {
public:
	Hierarchy(); 
	~Hierarchy();

	void Draw();
	void DrawRecursive(GameObject& game_object);
};