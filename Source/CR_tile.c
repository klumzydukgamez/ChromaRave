#include "CR_shared.h"

void CR_AppState_draw_tiles(CR_AppState* state) {
	for (int r = 0; r < CR_TILE_ROWS; r++) {
		for (int c = 0; c < CR_TILE_COLS; c++) {
			int tile = state->tiles[r][c];
			if (!tile)
				continue;
			CR_AppState_push_sprite(
				state, &state->tileSprites[tile],
				(vec3){
					(float)CR_TILE_WIDTH * c,
					(float)CR_TILE_HEIGHT * r,
					0.0f
				},
				(vec2){
					(float)CR_TILE_WIDTH,
					(float)CR_TILE_HEIGHT
				},
				(vec4){
					0.0f, 0.0f, 0.0f, 0.0f
				},
				false
			);
		}
	}
}
