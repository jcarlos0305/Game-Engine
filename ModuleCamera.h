#pragma once
#include "Module.h"

#include "MathGeoLib/Geometry/Frustum.h"
#include "MathGeoLib/Math/float3.h"
#include "MathGeoLib/Math/float3x4.h"
#include "MathGeoLib/Math/float4x4.h"

class ModuleCamera : public Module {
public:
	bool Init();

	void KeyboardMovement();
	void KeyboardRotation();

	void FreeLookAround(int x, int y);
	void ZoomCamera(int x, int y);

	void ResetCameraPosition();

	void SetPos(int x, int y, int z);

	UpdateStatus PreUpdate();
	UpdateStatus Update();
	UpdateStatus PostUpdate();

	inline float3   GetFront() const { return frustum.Front(); }
	inline float3   GetUp()    const { return frustum.Up(); }

	inline float3x4 GetWorldMatrix()            const { return frustum.WorldMatrix(); }
	inline float4x4 GetProjectionMatrix() const { return frustum.ProjectionMatrix(); }
	inline float4x4 GetViewMatrix()       const { return frustum.ViewMatrix(); }

	inline float GetNearPlane()     const { return frustum.NearPlaneDistance(); }
	inline float GetFarPlane()      const { return frustum.FarPlaneDistance(); }
	inline float GetHorizontalFOV() const { return frustum.HorizontalFov(); }
	inline float GetVerticalFOV()   const { return frustum.VerticalFov(); }
	inline float GetAspectRatio()   const { return frustum.AspectRatio(); }

	void SetAspectRatio(float aspect_ratio);

	bool CleanUp();

private:
	Frustum frustum;
	int speed_modifier = 1;
	
	void Rotate(float3x3 rotationMatrix);
};