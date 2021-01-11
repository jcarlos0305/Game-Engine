#pragma once

#include "Geometry/Frustum.h"
#include "Math/float3.h"
#include "Math/float3x4.h"
#include "Math/float4x4.h"

class Camera
{
public:
	Camera();
	~Camera();

	inline Frustum GetFrustum() const { return frustum; }

	inline float3   GetFront() const { return frustum.Front(); }
	inline float3   GetUp()    const { return frustum.Up(); }

	inline float3x4 GetWorldMatrix()      const { return frustum.WorldMatrix(); }
	inline float4x4 GetProjectionMatrix() const { return frustum.ProjectionMatrix(); }
	inline float4x4 GetViewMatrix()       const { return frustum.ViewMatrix(); }
	inline float4x4 GetViewProj()		  const { return frustum.ViewProjMatrix(); }

	inline float GetNearPlane()     const { return frustum.NearPlaneDistance(); }
	inline float GetFarPlane()      const { return frustum.FarPlaneDistance(); }
	inline float GetHorizontalFOV() const { return frustum.HorizontalFov(); }
	inline float GetVerticalFOV()   const { return frustum.VerticalFov(); }
	inline float GetAspectRatio()   const { return frustum.AspectRatio(); }

	inline void SetFront(float3& _vector) { frustum.SetFront(_vector); }
	inline void SetUp(float3& _vector) { frustum.SetUp(_vector); }
	inline void SetPos(float3& _vector) { frustum.SetPos(_vector); }
	inline void Translate(float3& _vector) { frustum.Translate(_vector); }

	void SetAspectRatio(float aspect_ratio);

private:
	Frustum frustum;
};

