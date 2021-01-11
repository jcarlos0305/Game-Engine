#pragma once

#include "Resources/Camera.h";
#include "Component.h"

class ComponentCamera : public Component {
public:
	ComponentCamera();
	~ComponentCamera();

	inline Camera* GetCamera() const { return camera; }
	inline Frustum GetFrustum() { return camera->GetFrustum(); }

private:
	Camera* camera = nullptr;
};