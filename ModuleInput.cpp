#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"
#include "ImGui/imgui_impl_sdl.h"

#include "LeakTest.h"

#define MAX_KEYS 300

ModuleInput::ModuleInput() : Module(), mouse({ 0, 0 }), mouse_motion({ 0,0 }) {
	keyboard = new KeyState[MAX_KEYS];
	memset(keyboard, static_cast<unsigned int>(KeyState::kKeyIdle), sizeof(KeyState) * MAX_KEYS);
	memset(mouse_buttons, static_cast<unsigned int>(KeyState::kKeyIdle), sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput() {}

// Called before render is available
bool ModuleInput::Init() {
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0) {
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
UpdateStatus ModuleInput::Update() {
	SDL_Event event;

	mouse_motion = { 0, 0 };
	mouse_wheel = 0;
	memset(window_events, false, static_cast<unsigned int>(WindowEvent::kCount) * sizeof(bool));

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i) {
		if (keys[i] == 1) {
			if (keyboard[i] == KeyState::kKeyIdle)
				keyboard[i] = KeyState::kKeyDown;
			else
				keyboard[i] = KeyState::kKeyRepeat;
		}
		else {
			if (keyboard[i] == KeyState::kKeyRepeat || keyboard[i] == KeyState::kKeyDown)
				keyboard[i] = KeyState::kKeyUp;
			else
				keyboard[i] = KeyState::kKeyIdle;
		}
	}

	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i) {
		if (mouse_buttons[i] == KeyState::kKeyDown)
			mouse_buttons[i] = KeyState::kKeyRepeat;

		if (mouse_buttons[i] == KeyState::kKeyUp)
			mouse_buttons[i] = KeyState::kKeyIdle;
	}

	while (SDL_PollEvent(&event) != 0) {
		ImGui_ImplSDL2_ProcessEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			window_events[static_cast<unsigned int>(WindowEvent::kQuit)] = true;
			break;

		case SDL_WINDOWEVENT:
			switch (event.window.event) {
				//case SDL_WINDOWEVENT_LEAVE:
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
				window_events[static_cast<unsigned int>(WindowEvent::kHide)] = true;
				break;

				//case SDL_WINDOWEVENT_ENTER:
			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
				window_events[static_cast<unsigned int>(WindowEvent::kShow)] = true;
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			mouse_buttons[event.button.button - 1] = KeyState::kKeyDown;
			break;

		case SDL_MOUSEBUTTONUP:
			mouse_buttons[event.button.button - 1] = KeyState::kKeyUp;
			break;

		case SDL_MOUSEMOTION:
			mouse_motion.x = event.motion.xrel / SCREEN_SIZE;
			mouse_motion.y = event.motion.yrel / SCREEN_SIZE;
			mouse.x = event.motion.x / SCREEN_SIZE;
			mouse.y = event.motion.y / SCREEN_SIZE;
			break;
		case SDL_MOUSEWHEEL:
			mouse_wheel = event.wheel.y;
			break;
		}
	}

	if (GetWindowEvent(WindowEvent::kQuit) == true || GetKey(SDL_SCANCODE_ESCAPE) == KeyState::kKeyDown)
		return UpdateStatus::kUpdateStop;

	return UpdateStatus::kUpdateContinue;
}

// Called before quitting
bool ModuleInput::CleanUp() {
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	delete keyboard;
	return true;
}
