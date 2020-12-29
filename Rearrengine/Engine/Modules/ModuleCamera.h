#pragma once

#include "Module.h"

#include "Geometry/Frustum.h"
#include "Math/float3.h"
#include "Math/float3x4.h"
#include "Math/float4x4.h"

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

	inline float3   GetFront() const { return frustum.Front(); }
	inline float3   GetUp()    const { return frustum.Up(); }

	inline float3x4 GetWorldMatrix()      const { return frustum.WorldMatrix(); }
	inline float4x4 GetProjectionMatrix() const { return frustum.ProjectionMatrix(); }
	inline float4x4 GetViewMatrix()       const { return frustum.ViewMatrix(); }

	inline float GetNearPlane()     const { return frustum.NearPlaneDistance(); }
	inline float GetFarPlane()      const { return frustum.FarPlaneDistance(); }
	inline float GetHorizontalFOV() const { return frustum.HorizontalFov(); }
	inline float GetVerticalFOV()   const { return frustum.VerticalFov(); }
	inline float GetAspectRatio()   const { return frustum.AspectRatio(); }

	void SetAspectRatio(float aspect_ratio);

	bool CleanUp() override;

private:
	Frustum frustum;
	float speed_modifier = 1.0f;
	
	void Rotate(const float3x3& rotationMatrix);
};