#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "Debug Draw/ModuleDebugDraw.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include "ModuleTexture.h"

#include "SDL.h"
#include <GL\glew.h>

#include "LeakTest.h"

// Called before render is available
bool ModuleRender::Init() {
	LOG("Creating Renderer context");

	SDL_GLContext context = SDL_GL_CreateContext(App->window->window);
	glewInit();

	/* Initializing OpenGL global states */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	/* Testing the module program and shaders with the classic lena */
	char* vertex_shader_url = App->program->LoadShaderSource("../vertex.glsl");
	if (vertex_shader_url) vertex_shader = App->program->CompileShader(GL_VERTEX_SHADER, vertex_shader_url);

	char* fragment_shader_url = App->program->LoadShaderSource("../fragment.glsl");
	if (fragment_shader_url) fragment_shader = App->program->CompileShader(GL_FRAGMENT_SHADER, fragment_shader_url);

	CreateVBO();
	program = App->program->CreateProgram(vertex_shader, fragment_shader);
	texture = App->texture->LoadTexture("img/Lenna.png");

	return true;
}

void ModuleRender::CreateVBO() {
	float vtx_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		0.5f, 1.0f
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);
}

void ModuleRender::RenderVBO(float4x4 proj, float4x4 view, float4x4 model) {
	glUseProgram(program);
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &proj[0][0]);
	glUniform1i(glGetUniformLocation(program, "mytexture"), 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * 3));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glDrawArrays(GL_TRIANGLES, 0, 3);
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

	float4x4 proj = App->camera->frustum.ProjectionMatrix();
	float4x4 view = App->camera->frustum.ViewMatrix();
	float4x4 model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f), float4x4::RotateZ(pi / 4.0f), float3(2.0f, 1.0f, 0.0f));

	RenderVBO(proj, view, model);

	// Drawing the grid with debug draw
	App->debug_draw->Draw(view, proj, w, h);
	return UpdateStatus::kUpdateContinue;
}

UpdateStatus ModuleRender::PostUpdate() {
	SDL_GL_SwapWindow(App->window->window);
	return UpdateStatus::kUpdateContinue;
}

// Called before quitting
bool ModuleRender::CleanUp() {
	LOG("Destroying renderer");

	// Delete VBO
	glDeleteBuffers(1, &vbo);

	//Destroy window
	SDL_GL_DeleteContext(context);

	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height) {}