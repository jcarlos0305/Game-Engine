#pragma once

#include "Utils/Globals.h"

#include <string>

class GameObject;

class Component {
public:
	Component() {};
	virtual ~Component() {};

	// Enable status
	inline void SetEnabled(bool enable) { enabled = enable; }
	inline bool IsEnabled() const { return enabled; }

	// Component type
	inline ComponentTypes GetType() const { return type; }

	// Component owner
	inline void SetOwner(GameObject* _game_object) { game_object = _game_object; }

	// Component JSON methods
	inline void SetUUID(std::string _uuid) { UUID = _uuid; };
	virtual bool ToJSON() const { return false; };

protected:
	bool enabled = false;
	ComponentTypes type = ComponentTypes::kUndefined;
	GameObject* game_object = nullptr;
	std::string UUID;
};
