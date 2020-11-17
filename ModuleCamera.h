#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleCamera : public Module {
public:
	bool Init();

	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();

	bool CleanUp();
};