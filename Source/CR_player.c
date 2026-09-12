#include "CR_shared.h"

void CR_AppState_update_player(CR_AppState* state) {
	ivec2 min;
	ivec2 max;

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
		state->playerVelocity[0] += SDL_copysignf(horizontalRate, horizontalDiff);

	state->playerPosition[0] += state->playerVelocity[0];

	min[0] = (int)(state->playerPosition[0] / CR_TILE_WIDTH);
	min[1] = (int)(state->playerPosition[1] / CR_TILE_HEIGHT);
	max[0] = (int)((state->playerPosition[0] + CR_PLAYER_COLLISION.w) / CR_TILE_WIDTH);
	max[1] = (int)((state->playerPosition[1] + CR_PLAYER_COLLISION.h) / CR_TILE_HEIGHT);

	if (min[0] < 0)
		min[0] = 0;
	if (min[1] < 0)
		min[1] = 0;
	if (max[0] >= CR_TILE_COLS)
		max[0] = CR_TILE_COLS - 1;
	if (max[1] >= CR_TILE_ROWS)
		max[1] = CR_TILE_ROWS - 1;

	for (int x = min[0]; x <= max[0]; x++) {
		for (int y = min[1]; y <= max[1]; y++) {
			if (!state->tiles[y][x])
				continue;
			vec2 tileMin = {
				x * CR_TILE_WIDTH,
				y * CR_TILE_HEIGHT
			};
			vec2 tileMax = {
				tileMin[0] + CR_TILE_WIDTH,
				tileMin[1] + CR_TILE_HEIGHT
			};
			if ((state->playerPosition[0] < tileMax[0] && (state->playerPosition[0] + CR_PLAYER_COLLISION.w) > tileMin[0]) &&
				(state->playerPosition[1] < tileMax[1] && (state->playerPosition[1] + CR_PLAYER_COLLISION.h) > tileMin[1])) {
				if (state->playerVelocity[0] > 0.0f)
					state->playerPosition[0] = tileMin[0] - CR_PLAYER_COLLISION.w;
				else if (state->playerVelocity[0] < 0.0f)
					state->playerPosition[0] = tileMax[0];
				state->playerVelocity[0] = 0.0f;
			}
		}
	}

	for (int i = 0; i < CR_MAX_ENEMIES; i++) {
		if (!state->enemies[i].alive)
			continue;
		SDL_FRect box = CR_ENEMY_COLLISIONS[state->enemies[i].type];
		vec2 eMin = {
			state->enemies[i].position[0],
			state->enemies[i].position[1]
		};
		vec2 eMax = {
			state->enemies[i].position[0] + box.w,
			state->enemies[i].position[1] + box.h
		};
		if ((state->playerPosition[0] < eMax[0] && (state->playerPosition[0] + CR_PLAYER_COLLISION.w) > eMin[0]) &&
			(state->playerPosition[1] < eMax[1] && (state->playerPosition[1] + CR_PLAYER_COLLISION.h) > eMin[1])) {
			if (state->playerVelocity[0] > 0.0f)
				state->playerPosition[0] = eMin[0] - CR_PLAYER_COLLISION.w;
			else if (state->playerVelocity[0] < 0.0f)
				state->playerPosition[0] = eMax[0];
			state->playerVelocity[0] = 0.0f;
		}
	}

	if (CR_AppState_keyboard_pressed(state, CR_PLAYER_JUMP))
		state->playerLastJumpTick = state->ticks;
	if (state->ticks - state->playerLastJumpTick <= CR_PLAYER_JUMP_TIME &&
		(state->playerOnGround || state->ticks - state->playerLastGroundTick <= CR_PLAYER_COYOTE_TIME)) {
		state->playerVelocity[1] = CR_PLAYER_JUMP_SPEED;
		state->playerOnGround = false;
		state->playerLastGroundTick = 0;
		state->playerLastJumpTick = 0;
	}
	if (CR_AppState_keyboard_up(state, CR_PLAYER_JUMP) &&
		state->playerVelocity[1] < 0.0f)
		state->playerVelocity[1] *= CR_PLAYER_SMALL_JUMP_SPEED;
	state->playerVelocity[1] += CR_PLAYER_GRAVITY;
	if (state->playerVelocity[1] >= CR_PLAYER_TERMINAL_VEL)
		state->playerVelocity[1] = CR_PLAYER_TERMINAL_VEL;

	state->playerPosition[1] += state->playerVelocity[1];

	min[0] = (int)(state->playerPosition[0] / CR_TILE_WIDTH);
	min[1] = (int)(state->playerPosition[1] / CR_TILE_HEIGHT);
	max[0] = (int)((state->playerPosition[0] + CR_PLAYER_COLLISION.w) / CR_TILE_WIDTH);
	max[1] = (int)((state->playerPosition[1] + CR_PLAYER_COLLISION.h) / CR_TILE_HEIGHT);

	if (min[0] < 0)
		min[0] = 0;
	if (min[1] < 0)
		min[1] = 0;
	if (max[0] >= CR_TILE_COLS)
		max[0] = CR_TILE_COLS - 1;
	if (max[1] >= CR_TILE_ROWS)
		max[1] = CR_TILE_ROWS - 1;

	state->playerOnGround = false;
	for (int x = min[0]; x <= max[0]; x++) {
		for (int y = min[1]; y <= max[1]; y++) {
			if (!state->tiles[y][x])
				continue;
			vec2 tileMin = {
				x * CR_TILE_WIDTH,
				y * CR_TILE_HEIGHT
			};
			vec2 tileMax = {
				tileMin[0] + CR_TILE_WIDTH,
				tileMin[1] + CR_TILE_HEIGHT
			};
			if ((state->playerPosition[0] < tileMax[0] && (state->playerPosition[0] + CR_PLAYER_COLLISION.w) > tileMin[0]) &&
				(state->playerPosition[1] < tileMax[1] && (state->playerPosition[1] + CR_PLAYER_COLLISION.h) > tileMin[1])) {
				if (state->playerVelocity[1] > 0.0f) {
					state->playerPosition[1] = tileMin[1] - CR_PLAYER_COLLISION.h;
					state->playerOnGround = true;
				} else if (state->playerVelocity[1] < 0.0f)
					state->playerPosition[1] = tileMax[1];
				state->playerVelocity[1] = 0.0f;
			}
		}
	}

	int closeEnemies = 0;
	float enemyThreat = 0.0f;
	for (int i = 0; i < CR_MAX_ENEMIES; i++) {
		if (!state->enemies[i].alive)
			continue;
		SDL_FRect box = CR_ENEMY_COLLISIONS[state->enemies[i].type];
		vec2 eMin = {
			state->enemies[i].position[0],
			state->enemies[i].position[1]
		};
		vec2 eMax = {
			state->enemies[i].position[0] + box.w,
			state->enemies[i].position[1] + box.h
		};
		if ((state->playerPosition[0] < eMax[0] && (state->playerPosition[0] + CR_PLAYER_COLLISION.w) > eMin[0]) &&
			(state->playerPosition[1] < eMax[1] && (state->playerPosition[1] + CR_PLAYER_COLLISION.h) > eMin[1])) {
			if (state->playerVelocity[1] > 0.0f) {
				state->playerPosition[1] = eMin[1] - CR_PLAYER_COLLISION.h;
				state->playerOnGround = true;
				state->playerPosition[0] += state->enemies[i].velocity[0];
			} else if (state->playerVelocity[1] < 0.0f)
				state->playerPosition[1] = eMax[1];
			state->playerVelocity[1] = 0.0f;
		}
		vec2 diff;
		glm_vec2_sub(state->enemies[i].position, state->playerPosition, diff);
		float dist = glm_vec2_norm(diff);
		if (dist < 300.0f) {
			closeEnemies++;
			enemyThreat += 1.0f - (dist / 300.0f);
		}
	}
	if (closeEnemies == 0)
		state->playerEnemyThreat = 0.0f;
	else {
		float crowd = (float)closeEnemies / (float)1;
		if (crowd > 1.0f)
			crowd = 1.0f;
		state->playerEnemyThreat = (enemyThreat / (float)closeEnemies) * crowd;
		if (state->playerEnemyThreat > 1.0f)
			state->playerEnemyThreat = 1.0f;
		if (state->playerEnemyThreat < 0.0f)
			state->playerEnemyThreat = 0.0f;
	}

	if (state->playerOnGround)
		state->playerLastGroundTick = state->ticks;

	vec2 cameraTarget;
	glm_vec2_copy(state->playerPosition, cameraTarget);
	glm_vec2_sub(cameraTarget, (vec2){-24.0f, -24.0f}, cameraTarget);
	glm_vec2_copy(cameraTarget, state->cameraTargetPosition);

	state->targetTimeScale = 1.0 - ((double)state->playerEnemyThreat * (1.0 - 0.5));
	state->cameraTargetZoom = 1.0f + (state->playerEnemyThreat * (1.5 - 1.0));

	if (state->playerOnGround) {
		if (state->playerAnimation == CR_EPlayerAnim_JUMP && state->playerFrameIndex < 3) {
			state->playerFrameIndex = 3;
			state->playerLastFrameTick = state->ticks;
		} else if (state->playerAnimation == CR_EPlayerAnim_JUMP && state->playerFrameIndex == 3) {
			Uint64 elapsed = state->ticks - state->playerLastFrameTick;
			if (elapsed >= CR_PLAYER_ANIM_TIMES[CR_EPlayerAnim_JUMP]) {
				if (SDL_fabsf(state->playerVelocity[0]) > 0.1f ||
					(CR_AppState_keyboard_down(state, CR_PLAYER_LEFT) || CR_AppState_keyboard_down(state, CR_PLAYER_RIGHT)))
					state->playerAnimation = CR_EPlayerAnim_RUN;
				else
					state->playerAnimation = CR_EPlayerAnim_IDLE;
			}
		} else {
			if (SDL_fabsf(state->playerVelocity[0]) > 0.1f ||
				(CR_AppState_keyboard_down(state, CR_PLAYER_LEFT) || CR_AppState_keyboard_down(state, CR_PLAYER_RIGHT)))
				state->playerAnimation = CR_EPlayerAnim_RUN;
			else
				state->playerAnimation = CR_EPlayerAnim_IDLE;
		}
	} else
		state->playerAnimation = CR_EPlayerAnim_JUMP;

	if (state->playerLastAnimation != state->playerAnimation) {
		if (state->playerAnimation != CR_EPlayerAnim_JUMP || state->playerOnGround)
			state->playerFrameIndex = 0;
		state->playerLastFrameTick = state->ticks;
		state->playerPlaying = true;
		state->playerLastAnimation = state->playerAnimation;
	}
	Uint64 elapsed = state->ticks - state->playerLastFrameTick;
	if (state->playerPlaying) {
		if (state->playerAnimation == CR_EPlayerAnim_JUMP) {
			if (state->playerVelocity[1] < 0.0f) {
				state->playerFrameIndex = 0;
				state->playerLastFrameTick = state->ticks;
			} else if (state->playerVelocity[1] >= 0.0f && state->playerFrameIndex < 3) {
				if (state->playerFrameIndex < 1) {
					state->playerFrameIndex = 1;
					state->playerLastFrameTick = state->ticks;
				} else {
					while (elapsed >= CR_PLAYER_ANIM_TIMES[CR_EPlayerAnim_JUMP]) {
						elapsed -= CR_PLAYER_ANIM_TIMES[CR_EPlayerAnim_JUMP];
						state->playerLastFrameTick += CR_PLAYER_ANIM_TIMES[state->playerAnimation];
						if (state->playerFrameIndex == 1) {
							state->playerFrameIndex = 2;
							break;
						}
					}
				}
			}
		} else {
			while (elapsed >= CR_PLAYER_ANIM_TIMES[state->playerAnimation]) {
				elapsed -= CR_PLAYER_ANIM_TIMES[state->playerAnimation];
				state->playerLastFrameTick += CR_PLAYER_ANIM_TIMES[state->playerAnimation];
				state->playerFrameIndex++;
				if (state->playerFrameIndex >= CR_PLAYER_ANIM_LENGTHS[state->playerAnimation])
					state->playerFrameIndex = 0;
			}
		}
	}
}

void CR_AppState_draw_player(CR_AppState* state) {
	float dir = SDL_copysignf(1.0f, state->playerVelocity[0]);
	if (state->playerVelocity[0] != 0 && dir > 0)
		state->playerFlip = false;
	if (state->playerVelocity[0] != 0 && dir < 0)
		state->playerFlip = true;
	vec2 offset;
	glm_vec2_zero(offset);
	if (state->playerFlip)
		glm_vec2_copy((float*)CR_PLAYER_FLIP_OFFSET, offset);
	CR_AppState_push_animated_sprite(
		state, &state->playerSprites[state->playerAnimation],
		(vec3){
			state->playerPosition[0] - offset[0] - CR_PLAYER_COLLISION.x,
			state->playerPosition[1] - offset[1] - CR_PLAYER_COLLISION.y,
			0.0f
		},
		(vec2){CR_PLAYER_WIDTH, CR_PLAYER_HEIGHT},
		(vec4){0.0f, 0.0f, 0.0f, 0.0f},
		state->playerFlip,
		CR_PLAYER_ANIM_LENGTHS[state->playerAnimation], state->playerFrameIndex
	);
}
