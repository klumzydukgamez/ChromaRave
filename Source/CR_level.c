#include "CR_shared.h"

bool CR_AppState_load_level(CR_AppState* state, SDL_Surface* surface, bool cleanup) {
	if (!surface) {
		CR_PANIC("Null Surface.");
		return false;
	}

	if (surface->w < CR_TILE_COLS || surface->h < CR_TILE_ROWS) {
		CR_PANIC("Level Surface Too Small.");
		if (cleanup)
			SDL_DestroySurface(surface);
		return false;
	}

	if (SDL_MUSTLOCK(surface)) {
		if (!SDL_LockSurface(surface)) {
			CR_PANIC("SDL_LockSurface failed. %s", SDL_GetError());
			if (cleanup)
				SDL_DestroySurface(surface);
			return false;
		}
	}

	for (int y = 0; y < CR_TILE_ROWS; y++) {
		for (int x = 0; x < CR_TILE_COLS; x++) {
			Uint8 r = 0;
			Uint8 g = 0;
			Uint8 b = 0;
			Uint8 a = 0;
			if (!SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a)) {
				CR_WARN("[%d, %d] SDL_ReadSurfacePixel failed. %s", x, y, SDL_GetError());
				continue;
			}
			if (r > CR_TILE_MAX)
				r = 0;
			state->tiles[y][x] = (int)r;
			switch (g) {
				case CR_LEVEL_GREEN_PLAYER:
					glm_vec2_copy(
						(vec2){
							CR_TILE_WIDTH * x, CR_TILE_HEIGHT * y
						},
						state->playerPosition
					);
					glm_vec2_copy(
						state->playerPosition,
						state->cameraPosition
					);
					break;
				default:
					break;
			}
		}
	}

	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);

	if (cleanup)
		SDL_DestroySurface(surface);

	return true;
}
