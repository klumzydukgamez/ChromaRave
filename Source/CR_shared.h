#if !defined __CR_SHARED_H__
#define __CR_SHARED_H__

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

#define CR_PANIC(format, ...) \
	SDL_Log("[PANIC][%s][%d] " format, __FILE_NAME__, __LINE__, ##__VA_ARGS__)

constexpr int CR_WIDTH = 640;
constexpr int CR_HEIGHT = 360;
constexpr float CR_ASPECT = (float)CR_WIDTH / (float)CR_HEIGHT;

extern const char* const CR_asset_finalVert;
extern const char* const CR_asset_finalFrag;

extern const Uint8* const CR_asset_defaultPng;
extern const size_t CR_asset_defaultPng_size;

GLuint CR_compile_shader(const char* const vertSource, const char* const fragSource);

SDL_Surface* CR_load_surface(const Uint8* data, size_t size);
GLuint CR_create_texture(int width, int height, bool wrap, const void* pixels);
void CR_update_texture(GLuint texture, const SDL_Surface* surface, int x, int y);

typedef struct {
	SDL_Window* window;
	SDL_GLContext glContext;

	SDL_Rect viewport;

	GLuint dummyVertexArray;

	GLuint finalShader;
	GLint finalUniformTexture;
	GLuint finalTexture;
	GLuint finalFramebuffer;
} CR_AppState;

bool CR_AppState_init(CR_AppState* state);
void CR_AppState_quit(CR_AppState* state);
bool CR_AppState_event(CR_AppState* state, SDL_Event* event);
bool CR_AppState_iterate(CR_AppState* state);

#endif /* __CR_SHARED_H__ */
