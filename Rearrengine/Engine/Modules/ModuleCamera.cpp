#include "Main/Application.h"
#include "Utils/Globals.h"
#include "ModuleCamera.h"
#include "ModuleInput.h"
#include "ModuleEditor.h"
#include "ModuleModel.h"
#include "UI/Viewport.h"

#include <SDL.h>
#include "Math/float3x3.h"
#include "Math/Quat.h"

#include "Utils/LeakTest.h"

bool ModuleCamera::Init() {
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.1f, 32.0f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD(90.0f), 1.3f);
	frustum.SetFront(-float3::unitZ);
	frustum.SetUp(float3::unitY);

	return true;
}

void ModuleCamera::Rotate(const float3x3& rotationMatrix) {
	frustum.SetFront(rotationMatrix.MulDir(frustum.Front().Normalized()));
	frustum.SetUp(rotationMatrix.MulDir(frustum.Up().Normalized()));
}

void ModuleCamera::KeyboardMovement() {
	float3 movement(0, 0, 0);

	// Up & down
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::kKeyRepeat && App->input->GetKey(SDL_SCANCODE_Q) == KeyState::kKeyRepeat) movement += float3::unitY;
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::kKeyRepeat && App->input->GetKey(SDL_SCANCODE_E) == KeyState::kKeyRepeat) movement -= float3::unitY;

	// Forward & backwards
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::kKeyRepeat && App->input->GetKey(SDL_SCANCODE_W) == KeyState::kKeyRepeat) movement += frustum.Front();
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::kKeyRepeat && App->input->GetKey(SDL_SCANCODE_S) == KeyState::kKeyRepeat) movement -= frustum.Front();

	// Left & right
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::kKeyRepeat && App->input->GetKey(SDL_SCANCODE_A) == KeyState::kKeyRepeat) movement -= frustum.WorldRight();
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::kKeyRepeat && App->input->GetKey(SDL_SCANCODE_D) == KeyState::kKeyRepeat) movement += frustum.WorldRight();

	frustum.Translate(movement * CAMERA_MOVEMENT_SPEED * speed_modifier * App->delta_time);
}

void ModuleCamera::KeyboardRotation() {
	float rotateY = 0.0f; float rotateX = 0.0f;

	// Pitch
	if (App->input->GetKey(SDL_SCANCODE_UP) == KeyState::kKeyRepeat) rotateX += 1;
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KeyState::kKeyRepeat) rotateX -= 1;

	// Yaw
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::kKeyRepeat) rotateY += 1;
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::kKeyRepeat) rotateY -= 1;

	Quat quatX(frustum.WorldRight(), rotateX * CAMERA_MOVEMENT_SPEED * speed_modifier * App->delta_time);
	Quat quatY(float3::unitY, rotateY * CAMERA_MOVEMENT_SPEED * speed_modifier * App->delta_time);

	Rotate(float3x3::FromQuat(quatY.Mul(quatX)));
}

void ModuleCamera::FreeLookAround(int x, int y) {
	float rotateX = 0.0f; float rotateY = 0.0f;

	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::kKeyRepeat && x != 0 && y != 0) {
		rotateX = -(float)y * App->delta_time * CAMERA_MOVEMENT_SPEED * speed_modifier;
		rotateY = -(float)x * App->delta_time * CAMERA_MOVEMENT_SPEED * speed_modifier;
	}

	Quat quatX(frustum.WorldRight(), rotateX * App->delta_time * CAMERA_MOVEMENT_SPEED * speed_modifier);
	Quat quatY(float3::unitY, rotateY * App->delta_time * CAMERA_MOVEMENT_SPEED * speed_modifier);

	Rotate(float3x3::FromQuat(quatY.Mul(quatX)));
}

//TODO ORBIT ATL + MB LEFT

void ModuleCamera::ZoomCamera(int x, int y) {
	float3 movement(0, 0, 0);

	if (App->input->GetKey(SDL_SCANCODE_LALT) == KeyState::kKeyRepeat &&
		App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::kKeyRepeat &&
		x != 0 && y != 0) {
		movement.z += (float)x;
		movement.z -= (float)y;
	}

	int mouse_wheel_movement = App->input->GetMouseWheel();

	if (mouse_wheel_movement != 0) {
		if (mouse_wheel_movement > 0) {
			movement += frustum.Front() * ZOOM_MOVEMENT_SPEED;
		}
		else {
			movement -= frustum.Front() * ZOOM_MOVEMENT_SPEED;
		}
	}

	frustum.Translate(movement * CAMERA_MOVEMENT_SPEED * speed_modifier * App->delta_time);
}

void ModuleCamera::ResetCameraPosition() {
	if (App->input->GetKey(SDL_SCANCODE_F) == KeyState::kKeyRepeat) {
		SetFocusToModel(App->model->GetModelCenterPoint(), App->model->GetModelRadius());
	}
}

void ModuleCamera::SetFocusToModel(float3 model_center, float radius) {
	frustum.SetPos(model_center + frustum.Front().Neg() * radius * 2.5);
}

void ModuleCamera::SetPos(float3 position) {
	frustum.SetPos(position);
}

UpdateStatus ModuleCamera::PreUpdate() {
	return UpdateStatus::kUpdateContinue;
}

UpdateStatus ModuleCamera::Update() {
	int x, y;
	SDL_GetRelativeMouseState(&x, &y);

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KeyState::kKeyRepeat) {
		speed_modifier = 2.0f;
	}
	else {
		speed_modifier = 1.0f;
	}

	if (App->editor->viewport->is_viewport_focused) {
		FreeLookAround(x, y);
		KeyboardMovement();
		KeyboardRotation();
		ZoomCamera(x, y);
		ResetCameraPosition();
	}

	return UpdateStatus::kUpdateContinue;
}

UpdateStatus ModuleCamera::PostUpdate() {
	return UpdateStatus::kUpdateContinue;
}

void ModuleCamera::SetAspectRatio(float aspect_ratio) {
	frustum.SetHorizontalFovAndAspectRatio(frustum.HorizontalFov(), aspect_ratio);
}

bool ModuleCamera::CleanUp() {
	return true;
}