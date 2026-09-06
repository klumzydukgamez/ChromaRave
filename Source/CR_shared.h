#if !defined __CR_SHARED_H__
#define __CR_SHARED_H__

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

#define CR_PANIC(format, ...) \
	SDL_Log("[PANIC][%s][%d] " format, __FILE_NAME__, __LINE__, ##__VA_ARGS__)

typedef struct {
	SDL_Window* window;
	SDL_GLContext glContext;
} CR_AppState;

bool CR_AppState_init(CR_AppState* state);
void CR_AppState_quit(CR_AppState* state);
bool CR_AppState_event(CR_AppState* state, SDL_Event* event);
bool CR_AppState_iterate(CR_AppState* state);

#endif /* __CR_SHARED_H__ */
