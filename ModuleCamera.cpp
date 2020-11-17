#include "ModuleCamera.h"

bool ModuleCamera::Init() {
    frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
    frustum.SetViewPlaneDistances(0.1f, 32.0f);
    frustum.SetHorizontalFovAndAspectRatio(DEGTORAD(90.0f), 1.3f);
    frustum.SetPos(float3(0, 3, -8));
    frustum.SetFront(float3::unitZ);
    frustum.SetUp(float3::unitY);

    return true;
}

update_status ModuleCamera::PreUpdate() {
    return update_status::UPDATE_CONTINUE;
}

update_status ModuleCamera::Update() {
    return update_status::UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate() {
    return update_status::UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp() {
    return true;
}
