#pragma once
#include "Module.h"
#include "MathGeoLib/Math/float4x4.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module {
public:
	bool Init();

	UpdateStatus PreUpdate();
	UpdateStatus Update();
	UpdateStatus PostUpdate();

	bool CleanUp();

	void WindowResized(unsigned width, unsigned height);

private:
	void* context = nullptr;
	unsigned int program = 0;
	
	/* Testing shaders & program module */
	void CreateVBO();
	void RenderVBO(float4x4 proj, float4x4 view, float4x4 model);
	unsigned int vertex_shader = 0;
	unsigned int fragment_shader = 0;
	unsigned int vbo = 0;
	unsigned int texture = 0;
};
