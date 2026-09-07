#include "CR_shared.h"

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

SDL_AppResult SDL_AppInit(void** appState, int argc, char** argv) {
	*appState = SDL_malloc(sizeof(CR_AppState));
	if (!*appState) {
		CR_PANIC("SDL_malloc failed. %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	if (!CR_AppState_init((CR_AppState*)*appState)) {
		CR_PANIC("CR_AppState_init failed.");
		return SDL_APP_FAILURE;
	}
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appState, SDL_AppResult result) {
	if (!appState) {
		CR_PANIC("Null AppState.");
		return;
	}
	CR_AppState_quit((CR_AppState*)appState);
	SDL_free(appState);
}

SDL_AppResult SDL_AppEvent(void* appState, SDL_Event* event) {
	if (!appState) {
		CR_PANIC("Null AppState.");
		return SDL_APP_FAILURE;
	}
	if (!CR_AppState_event((CR_AppState*)appState, event)) {
		CR_PANIC("CR_AppState_event terminated.");
		return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appState) {
	if (!appState) {
		CR_PANIC("Null AppState.");
		return SDL_APP_FAILURE;
	}
	if (!CR_AppState_iterate((CR_AppState*)appState)) {
		CR_PANIC("CR_AppState_iterate terminated.");
		return SDL_APP_FAILURE;
	}
	return SDL_APP_CONTINUE;
}
