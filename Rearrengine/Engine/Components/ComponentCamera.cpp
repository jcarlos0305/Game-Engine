#include "Main/Application.h"
#include "ComponentCamera.h"

ComponentCamera::ComponentCamera()
{
	type = ComponentTypes::kCamera;
	camera = new Camera();
}

ComponentCamera::~ComponentCamera()
{
	delete camera;
	camera = nullptr;
}
