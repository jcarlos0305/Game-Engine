#pragma once

#include "Module.h"
#include <Components/ComponentCamera.h>

class ModuleCamera : public Module {
public:
	bool Init() override;

	void KeyboardMovement();
	void KeyboardRotation();

	void FreeLookAround(int x, int y);
	void ZoomCamera(int x, int y);

	void ResetCameraPosition();

	void SetFocusToModel(float3 model_center, float radius = 1.0);

	void SetPos(float3 position);

	UpdateStatus PreUpdate() override;
	UpdateStatus Update() override;
	UpdateStatus PostUpdate() override;

	bool CleanUp() override;

	inline ComponentCamera* GetActiveCamera() { return activeCamera; }
	inline ComponentCamera* GetSceneCamera() const { return sceneCamera; }

	inline void SetActiveCamera(ComponentCamera* _camera) { activeCamera = _camera; }
	
	bool isGameCamera = false;

private:
	ComponentCamera* activeCamera = nullptr;
	ComponentCamera* sceneCamera = nullptr;
	float speed_modifier = 1.0f;
	
	void Rotate(const float3x3& rotationMatrix);
};