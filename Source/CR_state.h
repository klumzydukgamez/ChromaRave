#if !defined __CR_STATE_H__
#define __CR_STATE_H__

#include "CR_common.h"
#include "CR_constants.h"

typedef struct {
	SDL_Window* window;
	SDL_GLContext glContext;

	SDL_Rect viewport;

	Uint64 lastTime;
	double accumulator;
	double timeScale;
	double targetTimeScale;
	double time;
	Uint64 ticks;

	bool keyboardKeys[CR_MAX_KEYBOARD_KEYS];
	bool keyboardPreviousKeys[CR_MAX_KEYBOARD_KEYS];
	Uint64 keyboardKeyTimestamps[CR_MAX_KEYBOARD_KEYS];

	bool mouseButtons[CR_MAX_MOUSE_BUTTONS];
	bool mousePreviousButtons[CR_MAX_MOUSE_BUTTONS];
	Uint64 mouseButtonTimestamps[CR_MAX_MOUSE_BUTTONS];

	GLuint dummyVertexArray;

	GLuint finalShader;
	GLint finalUniformTexture;
	GLuint finalTexture;
	GLuint finalFramebuffer;

	struct {
		vec3 position;
		vec2 texCoord;
		vec4 color;
	} vertices[CR_MAX_VERTICES];
	int vertexCount;

	GLuint sceneShader;
	GLint sceneUniformProjView;
	GLint sceneUniformTexture;
	GLuint sceneVertexArray;
	GLuint sceneVertexBuffer;
	GLuint sceneElementBuffer;

	vec2 cameraPosition;
	vec2 cameraTargetPosition;
	float cameraZoom;
	float cameraTargetZoom;
	struct {
		vec2 origin;
		vec2 direction;
		float radius;
		float intensity;
		float decay;
	} cameraShakes[CR_MAX_CAMERA_SHAKES];
	int cameraShakeCount;
	mat4 cameraProjView;
	mat4 uiProjView;

	GLuint masterTexture;
	int masterX;
	int masterY;
	int masterOffset;

	SDL_FRect defaultSprite;
	SDL_FRect blankSprite;
	SDL_FRect overlaySprite;
	SDL_FRect backgroundSprites[CR_BACKGROUND_LAYER_COUNT];
	SDL_FRect tileSprites[CR_TILE_MAX];
	SDL_FRect enemySprites[CR_EEnemyType_COUNT][CR_EEnemyAnim_COUNT];
	SDL_FRect playerSprites[CR_EPlayerAnim_COUNT];

	int tiles[CR_TILE_ROWS][CR_TILE_COLS];

	struct {
		vec2 position;
		vec2 velocity;
		vec2 points[CR_MAX_ENEMY_POINTS];
		int pointCount;
		int currentPoint;
		int direction;
		bool alive;
		CR_EEnemyType type;
		CR_EEnemyAnim animation;
		CR_EEnemyAnim lastAnimation;
		int frameIndex;
		Uint64 lastFrameTick;
		bool playing;
		bool flip;
	} enemies[CR_MAX_ENEMIES];

	bool godMode;
	bool godModeBoost;

	vec2 playerPosition;
	vec2 playerVelocity;
	bool playerOnGround;
	Uint64 playerLastGroundTick;
	Uint64 playerLastJumpTick;
	CR_EPlayerAnim playerAnimation;
	CR_EPlayerAnim playerLastAnimation;
	int playerFrameIndex;
	Uint64 playerLastFrameTick;
	bool playerPlaying;
	bool playerFlip;
	float playerEnemyThreat;
} CR_AppState;

void CR_AppState_update_input(CR_AppState* state);
bool CR_AppState_keyboard_down(CR_AppState* state, SDL_Scancode key);
bool CR_AppState_keyboard_up(CR_AppState* state, SDL_Scancode key);
bool CR_AppState_keyboard_pressed(CR_AppState* state, SDL_Scancode key);
bool CR_AppState_keyboard_released(CR_AppState* state, SDL_Scancode key);
bool CR_AppState_keyboard_held(CR_AppState* state, SDL_Scancode key, Uint64 time);
bool CR_AppState_mouse_down(CR_AppState* state, int button);
bool CR_AppState_mouse_up(CR_AppState* state, int button);
bool CR_AppState_mouse_pressed(CR_AppState* state, int button);
bool CR_AppState_mouse_released(CR_AppState* state, int button);
bool CR_AppState_mouse_held(CR_AppState* state, int button, Uint64 time);

void CR_AppState_push_vertex(CR_AppState* state, const vec3 position, const vec2 texCoord, const vec4 color);
void CR_AppState_push_sprite(CR_AppState* state, const SDL_FRect* sprite, const vec3 position, const vec2 size, const vec4 color, bool flip);
void CR_AppState_push_animated_sprite(CR_AppState* state, const SDL_FRect* sprite, const vec3 position, const vec2 size, const vec4 color, bool flip, int length, int frame);
void CR_AppState_flush_vertices(CR_AppState* state, bool ui);

void CR_AppState_shake_camera(CR_AppState* state, vec2 origin, vec2 direction, float radius, float intensity, float decay);
void CR_AppState_update_camera(CR_AppState* state);

bool CR_AppState_pack_surface(CR_AppState* state, SDL_Surface* surface, SDL_FRect* sprite, bool cleanup);

void CR_AppState_draw_background(CR_AppState* state);

void CR_AppState_draw_tiles(CR_AppState* state);

void CR_AppState_update_enemies(CR_AppState* state);
void CR_AppState_draw_enemies(CR_AppState* state);

bool CR_AppState_load_level(CR_AppState* state, SDL_Surface* surface, bool cleanup);

void CR_AppState_update_player_god_mode(CR_AppState* state);
void CR_AppState_draw_player_god_mode(CR_AppState* state);

void CR_AppState_update_player(CR_AppState* state);
void CR_AppState_draw_player(CR_AppState* state);

bool CR_AppState_init(CR_AppState* state);
void CR_AppState_quit(CR_AppState* state);
bool CR_AppState_event(CR_AppState* state, SDL_Event* event);
bool CR_AppState_iterate(CR_AppState* state);

#endif /* __CR_STATE_H__ */
