#pragma once

#include "Utils/Globals.h"

class GameObject;

class Component {
public:
	Component() {};
	virtual ~Component() {};

	// Enable status
	virtual void SetEnabled(bool enable) { enabled = enable; }
	virtual bool IsEnabled() const { return enabled; }

	// Component type
	inline ComponentTypes GetType() const { return type; }

	// Component owner
	virtual void SetOwner(GameObject* _game_object) { game_object = _game_object; }

protected:
	bool enabled = false;
	ComponentTypes type = ComponentTypes::kUndefined;
	GameObject* game_object = nullptr;
};
