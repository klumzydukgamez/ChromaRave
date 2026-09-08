#include "CR_shared.h"

void CR_AppState_update_input(CR_AppState* state) {
	SDL_memcpy(
		state->keyboardPreviousKeys, state->keyboardKeys,
		sizeof(state->keyboardKeys)
	);
	SDL_memcpy(
		state->mousePreviousButtons, state->mouseButtons,
		sizeof(state->mouseButtons)
	);
}

bool CR_AppState_keyboard_down(CR_AppState* state, SDL_Scancode key) {
	if (key < 0 || key >= CR_MAX_KEYBOARD_KEYS)
		return false;
	return state->keyboardKeys[key];
}

bool CR_AppState_keyboard_up(CR_AppState* state, SDL_Scancode key) {
	if (key < 0 || key >= CR_MAX_KEYBOARD_KEYS)
		return false;
	return !state->keyboardKeys[key];
}

bool CR_AppState_keyboard_pressed(CR_AppState* state, SDL_Scancode key) {
	if (key < 0 || key >= CR_MAX_KEYBOARD_KEYS)
		return false;
	return state->keyboardKeys[key] && !state->keyboardPreviousKeys[key];
}

bool CR_AppState_keyboard_released(CR_AppState* state, SDL_Scancode key) {
	if (key < 0 || key >= CR_MAX_KEYBOARD_KEYS)
		return false;
	return !state->keyboardKeys[key] && state->keyboardPreviousKeys[key];
}

bool CR_AppState_keyboard_held(CR_AppState* state, SDL_Scancode key, Uint64 time) {
	if (key < 0 || key >= CR_MAX_KEYBOARD_KEYS)
		return false;
	if (!state->keyboardKeys[key])
		return false;
	return (SDL_GetTicks() - state->keyboardKeyTimestamps[key]) >= time;
}

bool CR_AppState_mouse_down(CR_AppState* state, int button) {
	if (button < 0 || button >= CR_MAX_MOUSE_BUTTONS)
		return false;
	return state->mouseButtons[button];
}

bool CR_AppState_mouse_up(CR_AppState* state, int button) {
	if (button < 0 || button >= CR_MAX_MOUSE_BUTTONS)
		return false;
	return !state->mouseButtons[button];
}

bool CR_AppState_mouse_pressed(CR_AppState* state, int button) {
	if (button < 0 || button >= CR_MAX_MOUSE_BUTTONS)
		return false;
	return state->mouseButtons[button] && !state->mousePreviousButtons[button];
}

bool CR_AppState_mouse_released(CR_AppState* state, int button) {
	if (button < 0 || button >= CR_MAX_MOUSE_BUTTONS)
		return false;
	return !state->mouseButtons[button] && state->mousePreviousButtons[button];
}

bool CR_AppState_mouse_held(CR_AppState* state, int button, Uint64 time) {
	if (button < 0 || button >= CR_MAX_MOUSE_BUTTONS)
		return false;
	if (!state->mouseButtons[button])
		return false;
	return (SDL_GetTicks() - state->mouseButtonTimestamps[button]) >= time;
}
