#pragma once
#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
#define M_PI 3.14159265358979323846f
#define DEGTORAD(angleDegrees) (((double) angleDegrees) * M_PI / 180.0)

void log(const char file[], int line, const char* format, ...);

// Application states
enum class MainStates {
	kMainCreation = 0,
	kMainStart,
	kMainUpdate,
	kMainFinish,
	kMainExit
};

// Update states
enum class UpdateStatus {
	kUpdateContinue = 1,
	kUpdateStop,
	kUpdateError
};

// Window events
enum class WindowEvent {
	kQuit = 0,
	kHide,
	kShow,
	kCount
};

// Key events
enum class KeyState {
	kKeyIdle = 0,
	kKeyDown,
	kKeyRepeat,
	kKeyUp
};

// Configuration -----------
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 768
#define SCREEN_SIZE 2
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Rearrengine"
#define CAMERA_MOVEMENT_SPEED 5.0f
#define ZOOM_MOVEMENT_SPEED 2.0f

// DEV info
#define REPO_URL "https://github.com/jcarlos0305/Game-Engine"
#define ENGINE_VERSION "1.0"
#define DEVELOPER "Juan Carlos Sanchez Guzman"
#define LICENCE "MIT License"

// Component types
enum class ComponentTypes {
	kMesh = 0,
	kCamera,
	kTransform,
	kUndefined
};

// Depth Quadtree
#define DEPTH_QUADTREE 3;