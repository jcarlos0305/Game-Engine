#pragma once
#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
#define PI 3.14159265358979323846f
#define DEGTORAD(angleDegrees) (((double) angleDegrees) * PI / 180.0)

void log(const char file[], int line, const char* format, ...);

enum class update_status {
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Rearrengine"