#include "PerformanceTimer.h"

#include <SDL.h>

PerformanceTimer::PerformanceTimer() : frequency(SDL_GetPerformanceFrequency()) {
	Start();
}

PerformanceTimer::~PerformanceTimer() {}

void PerformanceTimer::Start() {
	started_at = SDL_GetPerformanceCounter();
	stopped_at = 0;
}

double PerformanceTimer::Read() {
	return (SDL_GetPerformanceCounter() - started_at ) / frequency;
}

double PerformanceTimer::GetTick() {
	return SDL_GetPerformanceCounter() / frequency;
}

unsigned int PerformanceTimer::Stop() {
	if (!stopped_at) stopped_at = SDL_GetPerformanceCounter() - started_at;
	return stopped_at;
}