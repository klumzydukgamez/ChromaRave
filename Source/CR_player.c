#include "CR_shared.h"

void CR_AppState_update_player(CR_AppState* state) {
	float horizontalInput = (float)CR_AppState_keyboard_down(state, CR_PLAYER_RIGHT) -
							(float)CR_AppState_keyboard_down(state, CR_PLAYER_LEFT);
	float horizontalVel = horizontalInput * CR_PLAYER_MOVE_SPEED;
	float horizontalRate = CR_PLAYER_DECELERATION;
	if (SDL_fabsf(horizontalInput) > 0.0f)
		horizontalRate = CR_PLAYER_ACCELERATION;
	float horizontalDiff = horizontalVel - state->playerVelocity[0];
	if (SDL_fabsf(horizontalDiff) <= horizontalRate)
		state->playerVelocity[0] = horizontalVel;
	else
		state->playerVelocity[0] += copysignf(horizontalRate, horizontalDiff);

	if (SDL_fabsf(state->playerVelocity[0]) > 0.0f)
		state->cameraTargetZoom = 0.5f;
	else
		state->cameraTargetZoom = 1.0f;

	glm_vec2_add(state->playerPosition, state->playerVelocity, state->playerPosition);

	vec2 cameraTarget;
	glm_vec2_copy(state->playerPosition, cameraTarget);
	glm_vec2_sub(cameraTarget, (vec2){-24.0f, -24.0f}, cameraTarget);
	glm_vec2_copy(cameraTarget, state->cameraTargetPosition);

	if (SDL_fabsf(state->playerVelocity[0]) > 0.1f)
		state->playerAnimation = CR_EPlayerAnim_RUN;
	else
		state->playerAnimation = CR_EPlayerAnim_IDLE;

	Uint64 ticks = SDL_GetTicks();
	if (state->playerLastAnimation != state->playerAnimation) {
		state->playerFrameIndex = 0;
		state->playerLastFrameTick = ticks;
		state->playerPlaying = true;
		state->playerLastAnimation = state->playerAnimation;
	}
	Uint64 elapsed = ticks - state->playerLastFrameTick;
	if (state->playerPlaying) {
		while (elapsed >= CR_PLAYER_ANIM_TIMES[state->playerAnimation]) {
			elapsed -= CR_PLAYER_ANIM_TIMES[state->playerAnimation];
			state->playerLastFrameTick += CR_PLAYER_ANIM_TIMES[state->playerAnimation];
			state->playerFrameIndex++;
			if (state->playerFrameIndex >= CR_PLAYER_ANIM_LENGTHS[state->playerAnimation]) {
				state->playerFrameIndex = 0;
			}
		}
	}

	CR_AppState_push_sprite(
		state, &state->defaultSprite,
		(vec3){0.0f, 0.0f, 0.0f},
		(vec2){256.0f, 256.0f},
		(vec4){-0.5f, -0.5f, -0.5f, 1.0f},
		false
	);
	bool flip = SDL_copysignf(1.0f, state->playerVelocity[0]) < 0;
	vec2 offset;
	glm_vec2_zero(offset);
	if (flip)
		glm_vec2_copy((float*)CR_PLAYER_FLIP_OFFSET, offset);
	CR_AppState_push_animated_sprite(
		state, &state->playerSprites[state->playerAnimation],
		(vec3){
			state->playerPosition[0] - offset[0],
			state->playerPosition[1] - offset[1],
			0.0f
		},
		(vec2){48.0f, 48.0f},
		(vec4){0.0f, 0.0f, 0.0f, 0.0f},
		flip,
		CR_PLAYER_ANIM_LENGTHS[state->playerAnimation], state->playerFrameIndex
	);
}
