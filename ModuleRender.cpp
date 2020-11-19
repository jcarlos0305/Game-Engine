#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "Debug Draw/ModuleDebugDraw.h"
#include "SDL.h"
#include <GL\glew.h>

ModuleRender::ModuleRender() {}

// Destructor
ModuleRender::~ModuleRender() {}

// Called before render is available
bool ModuleRender::Init() {
	LOG("Creating Renderer context");

	SDL_GLContext context = SDL_GL_CreateContext(App->window->window);
	glewInit();

	/* Initializing OpenGL global states */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	return true;
}

UpdateStatus ModuleRender::PreUpdate() {
	// OpenGL Frame Init
	SDL_GetWindowSize(App->window->window, NULL, NULL);
	// Deleting color's buffer
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UpdateStatus::kUpdateContinue;
}

// Called every draw update
UpdateStatus ModuleRender::Update() {
	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);
	// Drawing the grid with debug draw
	App->debug_draw->Draw(App->camera->frustum.ViewMatrix(), App->camera->frustum.ProjectionMatrix(), w, h);
	return UpdateStatus::kUpdateContinue;
}

UpdateStatus ModuleRender::PostUpdate() {
	SDL_GL_SwapWindow(App->window->window);
	return UpdateStatus::kUpdateContinue;
}

// Called before quitting
bool ModuleRender::CleanUp() {
	LOG("Destroying renderer");

	//Destroy window
	SDL_GL_DeleteContext(context);

	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height) {}