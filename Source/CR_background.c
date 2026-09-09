#include "CR_shared.h"

void CR_AppState_draw_background(CR_AppState* state) {
	CR_AppState_push_sprite(
		state, &state->blankSprite,
		(vec3){0.0f, 0.0f, 0.0f},
		(vec2){CR_WIDTH, CR_HALF_HEIGHT},
		CR_BACKGROUND_TOP_COLOR,
		false
	);
	CR_AppState_push_sprite(
		state, &state->blankSprite,
		(vec3){0.0f, CR_HALF_HEIGHT, 0.0f},
		(vec2){CR_WIDTH, CR_HALF_HEIGHT},
		CR_BACKGROUND_BOTTOM_COLOR,
		false
	);

	CR_AppState_push_sprite(
		state, &state->backgroundSprites[0],
		(vec3){
			CR_HALF_WIDTH - (CR_BACKGROUND_WIDTH),
			CR_BACKGROUND_VERTICAL,
			0.0f
		},
		(vec2){576.0f, 324.0f},
		(vec4){0.0f, 0.0f, 0.0f, 0.0f},
		true
	);
	CR_AppState_push_sprite(
		state, &state->backgroundSprites[0],
		(vec3){
			CR_HALF_WIDTH,
			CR_BACKGROUND_VERTICAL,
			0.0f
		},
		(vec2){576.0f, 324.0f},
		(vec4){0.0f, 0.0f, 0.0f, 0.0f},
		true
	);

	CR_AppState_flush_vertices(state, true);

	for (int i = 1; i < CR_BACKGROUND_LAYER_COUNT; i++) {
		float x = SDL_fmodf(state->cameraPosition[0] * CR_BACKGROUND_FACTORS[i][0], CR_BACKGROUND_WIDTH);
		float y = SDL_fmodf(state->cameraPosition[1] * CR_BACKGROUND_FACTORS[i][1], CR_BACKGROUND_HEIGHT);
		if (x < 0.0f)
			x += CR_BACKGROUND_WIDTH;
		if (y < 0.0f)
			y += CR_BACKGROUND_HEIGHT;
		for (int r = 0; r < CR_BACKGROUND_ROWS; r++) {
			for (int c = 0; c < CR_BACKGROUND_COLS; c++) {
				CR_AppState_push_sprite(
					state, &state->backgroundSprites[i],
					(vec3){
						(state->cameraPosition[0] - x - CR_BACKGROUND_WIDTH) + (c * CR_BACKGROUND_WIDTH),
						(state->cameraPosition[1] - y - CR_BACKGROUND_HEIGHT) + (r * CR_BACKGROUND_HEIGHT),
						0.0f
					},
					(vec2){CR_BACKGROUND_WIDTH, CR_BACKGROUND_HEIGHT},
					(vec4){0.0f, 0.0f, 0.0f, 0.0f},
					true
				);
			}
		}
	}
}
