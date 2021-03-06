#include "Utils/Globals.h"
#include "Main/Application.h"
#include "ModuleWindow.h"

#include "Utils/LeakTest.h"

ModuleWindow::ModuleWindow() {}

// Destructor
ModuleWindow::~ModuleWindow() {}

// Called before render is available
bool ModuleWindow::Init() {
	LOG("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else {
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

		if (FULLSCREEN == true) {
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		/* Setting up the OpenGL attributes */
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); 
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if (window == NULL) {
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else {
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

bool ModuleWindow::CleanUp() {
	LOG("Destroying SDL window and quitting all SDL systems");

	if (window != NULL) {
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
	return true;
}