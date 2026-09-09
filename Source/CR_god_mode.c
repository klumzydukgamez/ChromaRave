#include "CR_shared.h"

void CR_AppState_update_player_god_mode(CR_AppState* state) {
	float horizontalInput = (float)CR_AppState_keyboard_down(state, CR_PLAYER_RIGHT) -
							(float)CR_AppState_keyboard_down(state, CR_PLAYER_LEFT);
	float horizontalVel = horizontalInput * CR_GOD_MODE_SPEED;
	float horizontalRate = CR_PLAYER_DECELERATION;
	if (SDL_fabsf(horizontalInput) > 0.0f)
		horizontalRate = CR_PLAYER_ACCELERATION;
	float horizontalDiff = horizontalVel - state->playerVelocity[0];
	if (SDL_fabsf(horizontalDiff) <= horizontalRate)
		state->playerVelocity[0] = horizontalVel;
	else
		state->playerVelocity[0] += copysignf(horizontalRate, horizontalDiff);

	float verticalInput = (float)CR_AppState_keyboard_down(state, CR_GOD_MODE_DOWN) -
						  (float)CR_AppState_keyboard_down(state, CR_GOD_MODE_UP);
	float verticalVel = verticalInput * CR_GOD_MODE_SPEED;
	float verticalRate = CR_PLAYER_DECELERATION;
	if (SDL_fabsf(verticalInput) > 0.0f)
		verticalRate = CR_PLAYER_ACCELERATION;
	float verticalDiff = verticalVel - state->playerVelocity[1];
	if (SDL_fabsf(verticalDiff) <= verticalRate)
		state->playerVelocity[1] = verticalVel;
	else
		state->playerVelocity[1] += copysignf(verticalRate, verticalDiff);

	glm_vec2_add(state->playerPosition, state->playerVelocity, state->playerPosition);

	vec2 cameraTarget;
	glm_vec2_copy(state->playerPosition, cameraTarget);
	glm_vec2_sub(cameraTarget, (vec2){-24.0f, -24.0f}, cameraTarget);
	glm_vec2_copy(cameraTarget, state->cameraTargetPosition);
}

void CR_AppState_draw_player_god_mode(CR_AppState* state) {
	float dir = SDL_copysignf(1.0f, state->playerVelocity[0]);
	if (state->playerVelocity[0] != 0 && dir > 0)
		state->playerFlip = false;
	if (state->playerVelocity[0] != 0 && dir < 0)
		state->playerFlip = true;
	vec2 offset;
	glm_vec2_zero(offset);
	if (state->playerFlip)
		glm_vec2_copy((float*)CR_PLAYER_FLIP_OFFSET, offset);
	CR_AppState_push_sprite(
		state, &state->playerSprites[CR_EPlayerAnim_GOD_MODE],
		(vec3){
			state->playerPosition[0] - offset[0],
			state->playerPosition[1] - offset[1],
			0.0f
		},
		(vec2){48.0f, 48.0f},
		(vec4){0.0f, 0.0f, 0.0f, 0.0f},
		state->playerFlip
	);
}
