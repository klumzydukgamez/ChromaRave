#include "CR_shared.h"

bool CR_AppState_event(CR_AppState* state, SDL_Event* event) {
	switch (event->type) {
		case SDL_EVENT_QUIT:
			return false;
		case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
			int w = 0;
			int h = 0;
			if (!SDL_GetWindowSizeInPixels(state->window, &w, &h)) {
				CR_PANIC("SDL_GetWindowSizeInPixels failed. %s", SDL_GetError());
				break;
			}
			float aspect = (float)w / (float)h;
			if (aspect >= CR_ASPECT) {
				state->viewport.w = (int)((float)h * CR_ASPECT);
				state->viewport.h = h;
				state->viewport.x = (w - state->viewport.w) / 2;
				state->viewport.y = 0;
			} else {
				state->viewport.w = w;
				state->viewport.h = (int)((float)w / CR_ASPECT);
				state->viewport.x = 0;
				state->viewport.y = (h - state->viewport.h) / 2;
			}
			break;
		case SDL_EVENT_KEY_DOWN:
			if (event->key.scancode == SDL_SCANCODE_D)
				state->cameraTargetZoom += 0.1;
			if (event->key.scancode == SDL_SCANCODE_A)
				state->cameraTargetZoom -= 0.1;
			if (event->key.scancode == SDL_SCANCODE_SPACE)
				CR_AppState_shake_camera(
					state, state->cameraPosition,
					(vec3){0.0f, 1.0f, 0.0f},
					10.0f, 100.0f, 0.75f
				);
		default:
			break;
	}

	return true;
}
