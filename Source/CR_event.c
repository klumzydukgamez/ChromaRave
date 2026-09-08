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
			if (!event->key.repeat && event->key.scancode < CR_MAX_KEYBOARD_KEYS) {
				state->keyboardKeys[event->key.scancode] = true;
				state->keyboardKeyTimestamps[event->key.scancode] = SDL_GetTicks();
			}
			break;
		case SDL_EVENT_KEY_UP:
			if (event->key.scancode < CR_MAX_KEYBOARD_KEYS)
				state->keyboardKeys[event->key.scancode] = false;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (event->button.button < CR_MAX_MOUSE_BUTTONS) {
				state->mouseButtons[event->button.button] = true;
				state->mouseButtonTimestamps[event->button.button] = SDL_GetTicks();
			}
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (event->button.button < CR_MAX_MOUSE_BUTTONS)
				state->mouseButtons[event->button.button] = true;
			break;
		default:
			break;
	}

	return true;
}
