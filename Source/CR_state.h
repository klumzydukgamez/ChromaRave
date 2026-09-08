#if !defined __CR_STATE_H__
#define __CR_STATE_H__

#include "CR_common.h"
#include "CR_constants.h"

typedef struct {
	SDL_Window* window;
	SDL_GLContext glContext;

	SDL_Rect viewport;

	bool keyboardKeys[CR_MAX_KEYBOARD_KEYS];
	bool keyboardPreviousKeys[CR_MAX_KEYBOARD_KEYS];
	Uint64 keyboardKeyTimestamps[CR_MAX_KEYBOARD_KEYS];

	bool mouseButtons[CR_MAX_MOUSE_BUTTONS];
	bool mousePreviousButtons[CR_MAX_MOUSE_BUTTONS];
	Uint64 mouseButtonTimestamps[CR_MAX_MOUSE_BUTTONS];

	GLuint dummyVertexArray;

	GLuint masterTexture;
	int masterX;
	int masterY;
	int masterOffset;

	SDL_FRect defaultSprite;

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

	GLuint sceneShader;
	GLint sceneUniformProjView;
	GLint sceneUniformTexture;

	struct {
		vec3 position;
		vec2 texCoord;
		vec4 color;
	} vertices[CR_MAX_VERTICES];
	int vertexCount;

	GLuint sceneVertexArray;
	GLuint sceneVertexBuffer;
	GLuint sceneElementBuffer;

	GLuint finalShader;
	GLint finalUniformTexture;
	GLuint finalTexture;
	GLuint finalFramebuffer;
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

void CR_AppState_shake_camera(CR_AppState* state, vec2 origin, vec2 direction, float radius, float intensity, float decay);
void CR_AppState_update_camera(CR_AppState* state);

bool CR_AppState_pack_surface(CR_AppState* state, SDL_Surface* surface, SDL_FRect* sprite, bool cleanup);

void CR_AppState_push_vertex(CR_AppState* state, const vec3 position, const vec2 texCoord, const vec4 color);
void CR_AppState_push_sprite(CR_AppState* state, const SDL_FRect* sprite, const vec3 position, const vec2 size, const vec4 color);
void CR_AppState_flush_vertices(CR_AppState* state);

bool CR_AppState_init(CR_AppState* state);
void CR_AppState_quit(CR_AppState* state);
bool CR_AppState_event(CR_AppState* state, SDL_Event* event);
bool CR_AppState_iterate(CR_AppState* state);

#endif /* __CR_STATE_H__ */
