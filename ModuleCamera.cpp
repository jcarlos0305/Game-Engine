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

UpdateStatus ModuleCamera::PreUpdate() {
    return UpdateStatus::kUpdateContinue;
}

UpdateStatus ModuleCamera::Update() {
    return UpdateStatus::kUpdateContinue;
}

UpdateStatus ModuleCamera::PostUpdate() {
    return UpdateStatus::kUpdateContinue;
}

bool ModuleCamera::CleanUp() {
    return true;
}
