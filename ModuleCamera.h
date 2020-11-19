#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib/Geometry/Frustum.h"

class ModuleCamera : public Module {
public:
	bool Init();

	void KeyboardMovement();
	void KeyboardRotation();
	void MouseMovement(int x, int y);
	void MouseRotation(int x, int y);

	UpdateStatus PreUpdate();
	UpdateStatus Update();
	UpdateStatus PostUpdate();

	bool CleanUp();

private:
	void Rotate(float3x3 rotationMatrix);

public:
	Frustum frustum;
};