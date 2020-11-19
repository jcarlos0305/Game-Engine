#pragma once
#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
#define M_PI 3.14159265358979323846f
#define DEGTORAD(angleDegrees) (((double) angleDegrees) * M_PI / 180.0)

void log(const char file[], int line, const char* format, ...);

enum class MainStates {
	kMainCreation = 0,
	kMainStart,
	kMainUpdate,
	kMainFinish,
	kMainExit
};

enum class UpdateStatus {
	kUpdateContinue = 1,
	kUpdateStop,
	kUpdateError
};

enum class WindowEvent {
	kQuit = 0,
	kHide,
	kShow,
	kCount
};

enum class KeyState {
	kKeyIdle = 0,
	kKeyDown,
	kKeyRepeat,
	kKeyUp
};

// Configuration -----------
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SCREEN_SIZE 2
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Rearrengine"