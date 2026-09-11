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
constexpr Uint64 CR_KEYBOARD_KEY_HOLD_TIME = 150;
constexpr int CR_MAX_MOUSE_BUTTONS = 9;
constexpr Uint64 CR_MOUSE_BUTTON_HOLD_TIME = 150;

constexpr int CR_MAX_SPRITES = 1024;
constexpr int CR_MAX_VERTICES = CR_MAX_SPRITES * 4;
constexpr int CR_MAX_INDICES = CR_MAX_SPRITES * 6;

constexpr float CR_CAMERA_NEAR = -100.0f;
constexpr float CR_CAMERA_FAR = 100.0f;
constexpr float CR_CAMERA_MOVE_SPEED = 0.15f;
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

constexpr int CR_MAX_ENEMIES = 96;
constexpr int CR_ENEMY_WIDTH = 48;
constexpr int CR_ENEMY_HEIGHT = 48;
constexpr int CR_MAX_ENEMY_POINTS = 10;
constexpr float CR_ENEMY_ACCELERATIONS[CR_EEnemyType_COUNT] = {
	[CR_EEnemyType_BATON_WARDEN] = 50.0f
};
constexpr float CR_ENEMY_DECELERATIONS[CR_EEnemyType_COUNT] = {
	[CR_EEnemyType_BATON_WARDEN] = 40.0f
};
constexpr float CR_ENEMY_SPEEDS[CR_EEnemyType_COUNT] = {
	[CR_EEnemyType_BATON_WARDEN] = 2.0f
};
constexpr int CR_ENEMY_ANIM_LENGTHS[CR_EEnemyType_COUNT][CR_EEnemyAnim_COUNT] = {
	[CR_EEnemyType_BATON_WARDEN][CR_EEnemyAnim_IDLE] = 4,
	[CR_EEnemyType_BATON_WARDEN][CR_EEnemyAnim_WALK] = 6
};
constexpr int CR_ENEMY_ANIM_TIMES[CR_EEnemyType_COUNT][CR_EEnemyAnim_COUNT] = {
	[CR_EEnemyType_BATON_WARDEN][CR_EEnemyAnim_IDLE] = 100,
	[CR_EEnemyType_BATON_WARDEN][CR_EEnemyAnim_WALK] = 100
};
constexpr SDL_FRect CR_ENEMY_COLLISIONS[CR_EEnemyType_COUNT] = {
	[CR_EEnemyType_BATON_WARDEN] = {6.0f, 18.0f, 16.0f, 30.0f}
};
constexpr vec2 CR_ENEMY_FLIP_OFFSETS[CR_EEnemyType_COUNT] = {
	[CR_EEnemyType_BATON_WARDEN] = {20.0f, 0.0}
};

constexpr int CR_LEVEL_PLAYER = 1;
constexpr int CR_LEVEL_ENEMY_POINT_MIN = 2;
constexpr int CR_LEVEL_ENEMY_POINT_MAX = CR_LEVEL_ENEMY_POINT_MIN + CR_MAX_ENEMY_POINTS - 1;

#if !defined CR_RELEASE
constexpr bool CR_ALLOW_GOD_MODE = true;
#else
constexpr bool CR_ALLOW_GOD_MODE = false;
#endif
constexpr SDL_Scancode CR_GOD_MODE = SDL_SCANCODE_G;
constexpr SDL_Scancode CR_GOD_MODE_UP = SDL_SCANCODE_W;
constexpr SDL_Scancode CR_GOD_MODE_DOWN = SDL_SCANCODE_S;
constexpr SDL_Scancode CR_GOD_MODE_BOOST = SDL_SCANCODE_SPACE;
constexpr float CR_GOD_MODE_SPEED = 8.0f;
constexpr float CR_GOD_MODE_BOOST_SPEED = 12.0f / CR_GOD_MODE_SPEED;

constexpr SDL_Scancode CR_PLAYER_LEFT = SDL_SCANCODE_A;
constexpr SDL_Scancode CR_PLAYER_RIGHT = SDL_SCANCODE_D;
constexpr SDL_Scancode CR_PLAYER_JUMP = SDL_SCANCODE_SPACE;
constexpr int CR_PLAYER_WIDTH = 48;
constexpr int CR_PLAYER_HEIGHT = 48;
constexpr int CR_PLAYER_ANIM_LENGTHS[CR_EPlayerAnim_COUNT] = {
	[CR_EPlayerAnim_GOD_MODE] = 0,
	[CR_EPlayerAnim_IDLE] = 4,
	[CR_EPlayerAnim_RUN] = 6,
	[CR_EPlayerAnim_JUMP] = 4
};
constexpr int CR_PLAYER_ANIM_TIMES[CR_EPlayerAnim_COUNT] = {
	[CR_EPlayerAnim_GOD_MODE] = 0,
	[CR_EPlayerAnim_IDLE] = 100,
	[CR_EPlayerAnim_RUN] = 100,
	[CR_EPlayerAnim_JUMP] = 100
};
constexpr SDL_FRect CR_PLAYER_COLLISION = {6.0f, 18.0f, 16.0f, 30.0f};
constexpr float CR_PLAYER_MOVE_SPEED = 5.0f;
constexpr float CR_PLAYER_JUMP_SPEED = -12.0f;
constexpr float CR_PLAYER_SMALL_JUMP_SPEED = -2.0f / CR_PLAYER_JUMP_SPEED;
constexpr Uint64 CR_PLAYER_JUMP_TIME = 75;
constexpr Uint64 CR_PLAYER_COYOTE_TIME = 75;
constexpr float CR_PLAYER_GRAVITY = 0.6f;
constexpr float CR_PLAYER_TERMINAL_VEL = 30.0f;
constexpr float CR_PLAYER_ACCELERATION = 50.0f;
constexpr float CR_PLAYER_DECELERATION = 40.0f;
constexpr vec2 CR_PLAYER_FLIP_OFFSET = {20.0f, 0.0f};

#endif /* __CR_CONSTANTS_H__ */
