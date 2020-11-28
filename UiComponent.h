#pragma once

#include "Globals.h"

class UiComponent {
public:

	UiComponent() {}
	virtual ~UiComponent() {}

	virtual void Draw() {}
	inline void Show(bool* new_state) { visible = new_state; }

public:
	bool visible = false;
	char* title = "";
};