#pragma once

#include "Globals.h"

class Application;

class Module {
public:

	Module() {}

	virtual bool Init() {
		return true;
	}

	virtual UpdateStatus PreUpdate() {
		return UpdateStatus::kUpdateContinue;
	}

	virtual UpdateStatus Update() {
		return UpdateStatus::kUpdateContinue;
	}

	virtual UpdateStatus PostUpdate() {
		return UpdateStatus::kUpdateContinue;
	}

	virtual bool CleanUp() {
		return true;
	}
};
