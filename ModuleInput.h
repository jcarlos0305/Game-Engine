#pragma once
#include "Module.h"
#include "Globals.h"
#include "Point.h"

#define NUM_MOUSE_BUTTONS 5

typedef unsigned __int8 Uint8;

class ModuleInput : public Module {
public:

	ModuleInput();
	~ModuleInput();

	bool         Init();
	UpdateStatus Update();
	bool         CleanUp();

	inline KeyState GetKey(int id) const { return keyboard[id]; }
	inline bool     GetWindowEvent(WindowEvent ev) const { return window_events[static_cast<unsigned int>(ev)]; }

private:
	bool      window_events[static_cast<unsigned int>(WindowEvent::kCount)];
	KeyState* keyboard;
	KeyState  mouse_buttons[NUM_MOUSE_BUTTONS];
	iPoint	  mouse_motion;
	iPoint	  mouse;
};