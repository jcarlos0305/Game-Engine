#pragma once

#include "Utils/Globals.h"

class Component {
public:
	Component() {};
	virtual ~Component() {};

	// Enable status
	inline void SetEnabled(bool enable) { enabled = enable; }
	inline bool IsEnabled() const { return enabled; }

	// Component type
	inline ComponentTypes GetType() const { return type; }

protected:
	bool enabled = false;
	ComponentTypes type = ComponentTypes::kUndefined;
};
