#include "Main/Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include "ModuleTexture.h"
#include "ModuleModel.h"
#include "ModuleScene.h"

#include "Math/float4x4.h"
#include "Debug Draw/ModuleDebugDraw.h"

#include <SDL.h>
#include <GL\glew.h>

#include "Utils/LeakTest.h"

ModuleRender::ModuleRender() {}

ModuleRender::~ModuleRender() {}

// Called before render is available
bool ModuleRender::Init() {
	LOG("Creating Renderer context");

	SDL_GLContext context = SDL_GL_CreateContext(App->window->window);
	glewInit();
	if (SDL_GL_SetSwapInterval(VSYNC) < 0)
		LOG("Warning: Unable to set VSync! SDL Error: %s", SDL_GetError());

	/* Initializing OpenGL global states */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glGenFramebuffers(1, &fbo);

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
	return UpdateStatus::kUpdateContinue;
}

UpdateStatus ModuleRender::PostUpdate() {
	SDL_GL_SwapWindow(App->window->window);

	return UpdateStatus::kUpdateContinue;
}

void ModuleRender::RenderToViewport(unsigned int width, unsigned int height) {
	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);

	float4x4 proj = App->camera->GetSceneCamera()->GetCamera()->GetProjectionMatrix();
	float4x4 view = App->camera->GetSceneCamera()->GetCamera()->GetViewMatrix();

	// Framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Deleting previous texture
	glDeleteTextures(1, &texture);

	// Creating texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Assign the texture to the frame buffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	// Creating the render buffer
	glDeleteRenderbuffers(1, &rbo);

	// Creating the render buffer
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);

	// Buffer use definition TODO: update w&h
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	glViewport(0, 0, width, height);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Drawing the model
	App->model->Draw();
	// Change draw to sen all the gameobjects that obb is inside the frustrum
	App->scene->Draw(*App->scene->GetRoot());

	// Drawing the grid with debug draw
	App->debug_draw->Draw(view, proj, w, h);

	// Drawing quads from GameObject to check its hitbox
	if (showQuad) App->debug_draw->DrawQuad();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Called before quitting
bool ModuleRender::CleanUp() {
	LOG("Destroying renderer");

	// Destroy buffers
	if (fbo != 0) glDeleteFramebuffers(1, &fbo);
	if (rbo != 0) glDeleteRenderbuffers(1, &rbo);
	if (texture != 0) glDeleteTextures(1, &texture);

	// Destroy window
	SDL_GL_DeleteContext(context);

	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height) {}