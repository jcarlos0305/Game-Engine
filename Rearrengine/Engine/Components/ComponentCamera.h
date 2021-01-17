#pragma once

#include "Resources/Camera.h";
#include "Component.h"

class ComponentCamera : public Component {
public:
	ComponentCamera();
	ComponentCamera(Json::Value& _component_camera, GameObject* _game_object);
	~ComponentCamera();

	inline Camera* GetCamera() const { return camera; }
	inline Frustum GetFrustum() { return camera->GetFrustum(); }

	void ToJson(Json::Value& _owner_root) const override;
	void FromJson(Json::Value& _component_data) override;

private:
	Camera* camera = nullptr;
};