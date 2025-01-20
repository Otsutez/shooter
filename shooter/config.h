#pragma once

// Window configuration
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

// Button configuration
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 50
#define BUTTON_ROUNDNESS 0.4f
#define BUTTON_SEGMENTS 20
#define BUTTON_DEFAULT_COLOR GOLD
#define BUTTON_HOVER_COLOR YELLOW
#define BUTTON_MIDCLICK_COLOR ORANGE
#define BUTTON_SPACING 20

// Input Box configuration
#define MAX_INPUT_CHARS 20
#define INPUT_BOX_WIDTH 400
#define INPUT_BOX_HEIGHT 50

// Player configuration
#define PLAYER_HEIGHT 2.0f
#define PLAYER1_START_X 8.0f
#define PLAYER1_START_Z 0.0f
#define PLAYER2_START_X -8.0f
#define PLAYER2_START_Z 0.0f
#define CAPSULE_RADIUS 0.5f
#define CAPSULE_SLICES 8
#define CAPSULE_RINGS 8
#define SPEED 60.0f
#define CAMERA_MOUSE_MOVE_SENSITIVITY 0.0015f

// Vector
#define ORIGIN Vector3 {0.0f, 0.0f, 0.0f}

// Map
#define MAP_WIDTH 20
#define MAP_LENGTH 20
#define TILE_SIZE 1.65f