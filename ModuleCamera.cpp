#include "ModuleCamera.h"

bool ModuleCamera::Init() {
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
