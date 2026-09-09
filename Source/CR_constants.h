#if !defined __CR_CONSTANTS_H__
#define __CR_CONSTANTS_H__

#include "CR_common.h"
#include "CR_enums.h"

constexpr int CR_WIDTH = 640;
constexpr int CR_HEIGHT = 360;
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
constexpr float CR_CAMERA_MOVE_SPEED = 0.08f;
constexpr float CR_CAMERA_ZOOM_SPEED = 0.04f;
constexpr int CR_MAX_CAMERA_SHAKES = 16;
constexpr float CR_MIN_CAMERA_SHAKE_INTENSITY = 0.05f;
constexpr float CR_MIN_CAMERA_SHAKE_DIRECTION = 0.01f;

constexpr int CR_MASTER_TEX_WIDTH = 1024;
constexpr int CR_MASTER_TEX_HEIGHT = 1024;
constexpr int CR_MASTER_TEX_PADDING = 2;

constexpr SDL_Scancode CR_PLAYER_LEFT = SDL_SCANCODE_A;
constexpr SDL_Scancode CR_PLAYER_RIGHT = SDL_SCANCODE_D;
constexpr float CR_PLAYER_MOVE_SPEED = 4.0f;
constexpr float CR_PLAYER_ACCELERATION = 50.0f;
constexpr float CR_PLAYER_DECELERATION = 40.0f;
constexpr vec2 CR_PLAYER_FLIP_OFFSET = {24.0f, 0.0f};

#endif /* __CR_CONSTANTS_H__ */
