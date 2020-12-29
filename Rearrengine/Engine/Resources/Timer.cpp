#include "Timer.h"

#include <SDL.h>

Timer::Timer() {}

Timer::~Timer() {}

void Timer::Start() {
	started_at = SDL_GetTicks();
	stopped_at = 0;
}

unsigned int Timer::Read() {
	return SDL_GetTicks() - started_at;
}

unsigned int Timer::Stop() {
	if (!stopped_at) stopped_at = SDL_GetTicks() - started_at;
	return stopped_at;
}
