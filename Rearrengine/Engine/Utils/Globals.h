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
#define DEPTH_QUADTREE 5;

// Default Texture
#define DEFAULT_TEXTURE_PATH "assets/GrayTexture.png"

/*
*	JSON property names
*/
#define JSON_ROOT_PATH "assets/"
#define JSON_FILE_EXTENSION ".json";

// Component
#define JSON_PROPERTY_ROTATION	"Rotation"
#define JSON_PROPERTY_SCALE		"Scale"
#define JSON_PROPERTY_TRANSLATE "Translate"
#define JSON_PROPERTY_TYPE		"Type"
#define JSON_PROPERTY_UUID		"UUID"
#define JSON_PROPERTY_NAME		"Name"

#define JSON_PROPERTY_COMPONENT_TRANSFORM	"Transform"
#define JSON_PROPERTY_COMPONENT_MESH		"Mesh"
#define JSON_PROPERTY_COMPONENT_MESH_PATH	"Mesh Path"

// Mesh
#define JSON_MESH_DIRECTORY					"Meshes/"
#define JSON_PROPERTY_MESH					"Mesh"
#define JSON_PROPERTY_MESH_VBO				"VBO"
#define JSON_PROPERTY_MESH_EBO				"EBO"

#define JSON_PROPERTY_MESH_NAME 			"Name"
#define JSON_PROPERTY_MESH_NUM_FACES 		"Num faces"
#define JSON_PROPERTY_MESH_NUM_INDICES		"Num indices"
#define JSON_PROPERTY_MESH_NUM_VERTICES 	"Num vertices"
#define JSON_PROPERTY_MESH_MATERIAL_INDEX 	"Material index"
#define JSON_PROPERTY_MESH_MIN_X 			"Min x"
#define JSON_PROPERTY_MESH_MIN_Y 			"Min y"
#define JSON_PROPERTY_MESH_MIN_Z 			"Min z"
#define JSON_PROPERTY_MESH_MAX_X 			"Max x"
#define JSON_PROPERTY_MESH_MAX_Y 			"Max y"
#define JSON_PROPERTY_MESH_MAX_Z 			"Max z"

// GameObject
#define JSON_PROPERTY_GAME_OBJECT				"Game Object"
#define JSON_PROPERTY_GAME_OBJECT_NAME			"Name"
#define JSON_PROPERTY_GAME_OBJECT_UUID			"UUID"
#define JSON_PROPERTY_GAME_OBJECT_PARENT_UUID	"Parent UUID"
#define JSON_PROPERTY_GAME_OBJECT_COMPONENTS	"Components"
#define JSON_PROPERTY_GAME_OBJECT_CHILDREN		"Children"

// Textures
#define JSON_TEXTURES_DIRECTORY					"Textures/"
#define JSON_PROPERTY_TEXTURES					"Textures"