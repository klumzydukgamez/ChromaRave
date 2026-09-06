#include "CR_shared.h"

bool CR_AppState_event(CR_AppState* state, SDL_Event* event) {
	switch (event->type) {
		case SDL_EVENT_QUIT:
			return false;
		default:
			break;
	}

	return true;
}
