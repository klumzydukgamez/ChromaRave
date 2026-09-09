#if !defined __CR_CONSTANTS_H__
#define __CR_CONSTANTS_H__

#include "CR_common.h"
#include "CR_enums.h"

constexpr int CR_WIDTH = 640;
constexpr int CR_HEIGHT = 360;
constexpr float CR_HALF_WIDTH = (float)CR_WIDTH / 2.0f;
constexpr float CR_HALF_HEIGHT = (float)CR_HEIGHT / 2.0f;
constexpr float CR_ASPECT = (float)CR_WIDTH / (float)CR_HEIGHT;

constexpr int CR_MAX_KEYBOARD_KEYS = SDL_SCANCODE_COUNT;
constexpr Uint64 CR_KEYBOARD_KEY_HOLD_TIME = 250;
constexpr int CR_MAX_MOUSE_BUTTONS = 9;
constexpr Uint64 CR_MOUSE_BUTTON_HOLD_TIME = 250;

constexpr int CR_MAX_SPRITES = 1024;
constexpr int CR_MAX_VERTICES = CR_MAX_SPRITES * 4;
constexpr int CR_MAX_INDICES = CR_MAX_SPRITES * 6;

constexpr float CR_CAMERA_NEAR = -100.0f;
constexpr float CR_CAMERA_FAR = 100.0f;
constexpr float CR_CAMERA_MOVE_SPEED = 0.06f;
constexpr float CR_CAMERA_ZOOM_SPEED = 0.04f;
constexpr int CR_MAX_CAMERA_SHAKES = 16;
constexpr float CR_MIN_CAMERA_SHAKE_INTENSITY = 0.05f;
constexpr float CR_MIN_CAMERA_SHAKE_DIRECTION = 0.01f;

constexpr int CR_MASTER_TEX_WIDTH = 2048;
constexpr int CR_MASTER_TEX_HEIGHT = 2048;
constexpr int CR_MASTER_TEX_PADDING = 2;

constexpr int CR_BACKGROUND_LAYER_COUNT = 5;
constexpr float CR_BACKGROUND_WIDTH = 576.0f;
constexpr float CR_BACKGROUND_HEIGHT = 364.0f;
constexpr float CR_BACKGROUND_VERTICAL = CR_HALF_HEIGHT - (CR_BACKGROUND_HEIGHT / 3.0f);
constexpr vec4 CR_BACKGROUND_TOP_COLOR = {
	92.0f / 255.0f,
	89.0f / 255.0f,
	92.0f / 255.0f,
	1.0f
};
constexpr vec4 CR_BACKGROUND_BOTTOM_COLOR = {
	128.0f / 255.0f,
	128.0f / 255.0f,
	128.0f / 255.0f,
	1.0f
};
constexpr int CR_BACKGROUND_COLS = 3;
constexpr int CR_BACKGROUND_ROWS = 3;
constexpr vec2 CR_BACKGROUND_FACTORS[CR_BACKGROUND_LAYER_COUNT] = {
	{0.0f, 0.0f},
	{0.15f, 0.08f},
	{0.35f, 0.20f},
	{0.60f, 0.40f},
	{0.85f, 0.65f}
};

constexpr int CR_TILE_COLS = 512;
constexpr int CR_TILE_ROWS = 256;
constexpr int CR_TILE_MAX = 126 + 1;
constexpr int CR_TILE_WIDTH = 32;
constexpr int CR_TILE_HEIGHT = 32;

constexpr int CR_LEVEL_GREEN_PLAYER = 1;

constexpr bool CR_ALLOW_GOD_MODE = true;
constexpr SDL_Scancode CR_GOD_MODE = SDL_SCANCODE_G;
constexpr SDL_Scancode CR_GOD_MODE_UP = SDL_SCANCODE_W;
constexpr SDL_Scancode CR_GOD_MODE_DOWN = SDL_SCANCODE_S;
constexpr float CR_GOD_MODE_SPEED = 8.0f;

constexpr SDL_Scancode CR_PLAYER_LEFT = SDL_SCANCODE_A;
constexpr SDL_Scancode CR_PLAYER_RIGHT = SDL_SCANCODE_D;
constexpr float CR_PLAYER_MOVE_SPEED = 4.0f;
constexpr float CR_PLAYER_ACCELERATION = 50.0f;
constexpr float CR_PLAYER_DECELERATION = 40.0f;
constexpr vec2 CR_PLAYER_FLIP_OFFSET = {24.0f, 0.0f};

#endif /* __CR_CONSTANTS_H__ */
