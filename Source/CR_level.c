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

			int i = (int)b;
			if (g == CR_LEVEL_PLAYER) {
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
			} else if (g >= CR_LEVEL_ENEMY_POINT_MIN && g <= CR_LEVEL_ENEMY_POINT_MAX) {
				int index = g - CR_LEVEL_ENEMY_POINT_MIN;
				glm_vec2_copy(
					(vec2){CR_TILE_WIDTH * x, CR_TILE_HEIGHT * y},
					state->enemies[i].points[index]
				);
				if (index + 1 > state->enemies[i].pointCount)
					state->enemies[i].pointCount = index + 1;
			} else if (g > CR_LEVEL_ENEMY_POINT_MAX) {
				state->enemies[i].type = (CR_EEnemyType)(g - CR_LEVEL_ENEMY_POINT_MAX - 1);
				glm_vec2_copy(
					(vec2){CR_TILE_WIDTH * x, CR_TILE_HEIGHT * y},
					state->enemies[i].position
				);
				state->enemies[i].alive = true;
				state->enemies[i].animation = CR_EEnemyAnim_IDLE;
				state->enemies[i].lastAnimation = CR_EEnemyAnim_IDLE;
				state->enemies[i].frameIndex = 0;
				state->enemies[i].lastFrameTick = SDL_GetTicks();
				state->enemies[i].playing = true;
				state->enemies[i].flip = false;
			}
		}
	}

	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);

	if (cleanup)
		SDL_DestroySurface(surface);

	return true;
}
