#include "CR_shared.h"

void CR_AppState_update_player_god_mode(CR_AppState* state) {
	float speed = CR_GOD_MODE_SPEED;
	if (CR_AppState_keyboard_held(state, CR_GOD_MODE_BOOST, CR_KEYBOARD_KEY_HOLD_TIME)) {
		state->godModeBoost = true;
		speed *= CR_GOD_MODE_BOOST_SPEED;
	} else
		state->godModeBoost = false;

	vec2 input = {
		(float)CR_AppState_keyboard_down(state, CR_PLAYER_RIGHT) -
			(float)CR_AppState_keyboard_down(state, CR_PLAYER_LEFT),
		(float)CR_AppState_keyboard_down(state, CR_GOD_MODE_DOWN) -
			(float)CR_AppState_keyboard_down(state, CR_GOD_MODE_UP)
	};
	glm_vec2_normalize(input);
	vec2 vel;
	glm_vec2_scale(input, speed, vel);
	vec2 rate = {CR_PLAYER_DECELERATION, CR_PLAYER_DECELERATION};
	if (SDL_fabsf(vel[0]) > 0.0f)
		rate[0] = CR_PLAYER_ACCELERATION;
	if (SDL_fabsf(vel[1]) > 0.0f)
		rate[1] = CR_PLAYER_ACCELERATION;
	vec2 diff;
	glm_vec2_sub(vel, state->playerVelocity, diff);
	if (SDL_fabsf(diff[0]) <= rate[0])
		state->playerVelocity[0] = vel[0];
	else
		state->playerVelocity[0] += copysignf(rate[0], diff[0]);
	if (SDL_fabsf(diff[1]) <= rate[1])
		state->playerVelocity[1] = vel[1];
	else
		state->playerVelocity[1] += copysignf(rate[1], diff[1]);

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
	CR_EPlayerAnim anim = CR_EPlayerAnim_IDLE;
	if (state->godModeBoost)
		anim = CR_EPlayerAnim_GOD_MODE;
	CR_AppState_push_animated_sprite(
		state, &state->playerSprites[anim],
		(vec3){
			state->playerPosition[0] - offset[0],
			state->playerPosition[1] - offset[1],
			0.0f
		},
		(vec2){48.0f, 48.0f},
		(vec4){0.0f, 0.0f, 0.0f, 0.0f},
		state->playerFlip,
		CR_PLAYER_ANIM_LENGTHS[anim], 0
	);
}
