#include "Main/Application.h"
#include "ComponentCamera.h"

ComponentCamera::ComponentCamera()
{
	type = ComponentTypes::kCamera;
	camera = new Camera();

	// Drawing frustum camera
	// App->debug_draw->DrawFrustumCamera(App->camera->GetTest());
}

ComponentCamera::~ComponentCamera()
{
	delete camera;
	camera = nullptr;
}
