#include "Camera.h"
#include "Utils/Globals.h"
#include "Utils/UUID.h"

Camera::Camera() : UUID(custom_UUID::generate())
{
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetViewPlaneDistances(0.5f, 50.0f);
	frustum.SetHorizontalFovAndAspectRatio(DEGTORAD(90.0f), 1.3f);
	frustum.SetFront(-float3::unitZ);
	frustum.SetUp(float3::unitY);
	frustum.SetPos(float3(0, 3, 12));
}

Camera::~Camera()
{
}

void Camera::SetAspectRatio(float aspect_ratio) {
	frustum.SetHorizontalFovAndAspectRatio(frustum.HorizontalFov(), aspect_ratio);
}