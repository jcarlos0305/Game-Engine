#pragma once
#include "Module.h"

#include "Utils/Point.h"

#define NUM_MOUSE_BUTTONS 5

typedef unsigned __int8 Uint8;

class ModuleInput : public Module {
public:

	ModuleInput();
	~ModuleInput();

	bool         Init() override;
	UpdateStatus Update() override;
	bool         CleanUp() override;

	inline KeyState GetKey(int id) const { return keyboard[id]; }
	inline KeyState GetMouseButtonDown(int id) const { return mouse_buttons[id - 1]; }
	inline bool     GetWindowEvent(WindowEvent ev) const { return window_events[static_cast<unsigned int>(ev)]; }
	inline int      GetMouseWheel() const { return mouse_wheel; }

private:
	bool      window_events[static_cast<unsigned int>(WindowEvent::kCount)];
	KeyState* keyboard;
	KeyState  mouse_buttons[NUM_MOUSE_BUTTONS];
	iPoint	  mouse_motion;
	iPoint	  mouse;
	int       mouse_wheel = 0;
};