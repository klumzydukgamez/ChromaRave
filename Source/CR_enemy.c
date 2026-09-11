#include "CR_shared.h"

void CR_AppState_update_enemies(CR_AppState* state) {
	for (int i = 0; i < CR_MAX_ENEMIES; i++) {
		if (!state->enemies[i].alive)
			continue;
		if (state->enemies[i].pointCount <= 1)
			continue;
		Uint64 ticks = SDL_GetTicks();
		CR_EEnemyType type = state->enemies[i].type;
		SDL_FRect box = CR_ENEMY_COLLISIONS[type];
		vec2 target;
		glm_vec2_copy(state->enemies[i].points[state->enemies[i].currentPoint], target);
		target[1] += (float)CR_TILE_HEIGHT - box.h;
		vec2 diff;
		glm_vec2_sub(target, state->enemies[i].position, diff);
		float dist = glm_vec2_norm(diff);
		if (dist <= 1.0f) {
			glm_vec2_copy(target, state->enemies[i].position);
			if (state->enemies[i].currentPoint >= state->enemies[i].pointCount - 1) {
				state->enemies[i].currentPoint = state->enemies[i].pointCount - 1;
				state->enemies[i].direction = -1;
			} else if (state->enemies[i].currentPoint <= 0) {
				state->enemies[i].currentPoint = 0;
				state->enemies[i].direction = 1;
			}
			state->enemies[i].currentPoint += state->enemies[i].direction;
			glm_vec2_copy(state->enemies[i].points[state->enemies[i].currentPoint], target);
			glm_vec2_sub(target, state->enemies[i].position, diff);
			dist = glm_vec2_norm(diff);
		}
		vec2 input = {0.0f, 0.0f};
		if (dist > 0.0f)
			glm_vec2_normalize_to(diff, input);
		vec2 vel;
		glm_vec2_scale(input, CR_ENEMY_SPEEDS[type], vel);
		vec2 rate = {CR_ENEMY_DECELERATIONS[type], CR_ENEMY_DECELERATIONS[type]};
		if (SDL_fabsf(input[0]) > 0.0f)
			rate[0] = CR_ENEMY_ACCELERATIONS[type];
		if (SDL_fabsf(input[1]) > 0.0f)
			rate[1] = CR_ENEMY_ACCELERATIONS[type];
		vec2 velDiff;
		glm_vec2_sub(vel, state->enemies[i].velocity, velDiff);
		if (SDL_fabsf(velDiff[0]) <= rate[0])
			state->enemies[i].velocity[0] = vel[0];
		else
			state->enemies[i].velocity[0] += SDL_copysignf(rate[0], velDiff[0]);
		if (SDL_fabsf(velDiff[1]) <= rate[1])
			state->enemies[i].velocity[1] = vel[1];
		else
			state->enemies[i].velocity[1] += SDL_copysignf(rate[1], velDiff[1]);

		ivec2 min;
		ivec2 max;

		state->enemies[i].position[0] += state->enemies[i].velocity[0];

		min[0] = (int)(state->enemies[i].position[0] / CR_TILE_WIDTH);
		min[1] = (int)(state->enemies[i].position[1] / CR_TILE_HEIGHT);
		max[0] = (int)((state->enemies[i].position[0] + box.w) / CR_TILE_WIDTH);
		max[1] = (int)((state->enemies[i].position[1] + box.h) / CR_TILE_HEIGHT);

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
				if ((state->enemies[i].position[0] < tileMax[0] && (state->enemies[i].position[0] + box.w) > tileMin[0]) &&
					(state->enemies[i].position[1] < tileMax[1] && (state->enemies[i].position[1] + box.h) > tileMin[1])) {
					if (state->enemies[i].velocity[0] > 0.0f) {
						state->enemies[i].position[0] = tileMin[0] - box.w;
					} else if (state->enemies[i].velocity[0] < 0.0f)
						state->enemies[i].position[0] = tileMax[0];
					state->enemies[i].velocity[0] = 0.0f;
				}
			}
		}

		if (!state->godMode) {
			if ((state->enemies[i].position[0] < (state->playerPosition[0] + CR_PLAYER_COLLISION.w) && (state->enemies[i].position[0] + box.w) > state->playerPosition[0]) &&
				(state->enemies[i].position[1] < (state->playerPosition[1] + CR_PLAYER_COLLISION.h) && (state->enemies[i].position[1] + box.h) > state->playerPosition[1])) {
				if (state->enemies[i].velocity[0] > 0.0f)
					state->enemies[i].position[0] = state->playerPosition[0] - box.w;
				else if (state->enemies[i].velocity[0] < 0.0f)
					state->enemies[i].position[0] = state->playerPosition[0] + CR_PLAYER_COLLISION.w;
				state->enemies[i].velocity[0] = 0.0f;
			}
		}

		state->enemies[i].position[1] += state->enemies[i].velocity[1];

		min[0] = (int)(state->enemies[i].position[0] / CR_TILE_WIDTH);
		min[1] = (int)(state->enemies[i].position[1] / CR_TILE_HEIGHT);
		max[0] = (int)((state->enemies[i].position[0] + box.w) / CR_TILE_WIDTH);
		max[1] = (int)((state->enemies[i].position[1] + box.h) / CR_TILE_HEIGHT);

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
				if ((state->enemies[i].position[0] < tileMax[0] && (state->enemies[i].position[0] + box.w) > tileMin[0]) &&
					(state->enemies[i].position[1] < tileMax[1] && (state->enemies[i].position[1] + box.h) > tileMin[1])) {
					if (state->enemies[i].velocity[1] > 0.0f) {
						state->enemies[i].position[1] = tileMin[1] - box.h;
					} else if (state->enemies[i].velocity[1] < 0.0f)
						state->enemies[i].position[1] = tileMax[1];
					state->enemies[i].velocity[1] = 0.0f;
				}
			}
		}

		if (!state->godMode) {
			if ((state->enemies[i].position[0] < (state->playerPosition[0] + CR_PLAYER_COLLISION.w) && (state->enemies[i].position[0] + box.w) > state->playerPosition[0]) &&
				(state->enemies[i].position[1] < (state->playerPosition[1] + CR_PLAYER_COLLISION.h) && (state->enemies[i].position[1] + box.h) > state->playerPosition[1])) {
				if (state->enemies[i].velocity[1] > 0.0f)
					state->enemies[i].position[1] = state->playerPosition[1] - box.h;
				else if (state->enemies[i].velocity[1] < 0.0f)
					state->enemies[i].position[1] = state->playerPosition[1] + CR_PLAYER_COLLISION.h;
				state->enemies[i].velocity[1] = 0.0f;
			}
		}

		if (SDL_fabsf(state->enemies[i].velocity[0]) > 0.1f ||
			SDL_fabsf(input[0]) > 0.1f)
			state->enemies[i].animation = CR_EEnemyAnim_WALK;
		else
			state->enemies[i].animation = CR_EEnemyAnim_IDLE;

		if (state->enemies[i].lastAnimation != state->enemies[i].animation) {
			state->enemies[i].frameIndex = 0;
			state->enemies[i].lastFrameTick = ticks;
			state->enemies[i].playing = true;
			state->enemies[i].lastAnimation = state->enemies[i].animation;
		}

		CR_EEnemyAnim animation = state->enemies[i].animation;
		Uint64 elapsed = ticks - state->enemies[i].lastFrameTick;
		if (state->enemies[i].playing) {
			while (elapsed >= CR_ENEMY_ANIM_TIMES[type][animation]) {
				elapsed -= CR_ENEMY_ANIM_TIMES[type][animation];
				state->enemies[i].lastFrameTick += CR_ENEMY_ANIM_TIMES[type][animation];
				state->enemies[i].frameIndex++;
				if (state->enemies[i].frameIndex >= CR_ENEMY_ANIM_LENGTHS[type][animation])
					state->enemies[i].frameIndex = 0;
			}
		}
	}
}

void CR_AppState_draw_enemies(CR_AppState* state) {
	for (int i = 0; i < CR_MAX_ENEMIES; i++) {
		if (!state->enemies[i].alive)
			continue;
		float dir = SDL_copysignf(1.0f, state->enemies[i].velocity[0]);
		if (state->enemies[i].velocity[0] != 0 && dir > 0)
			state->enemies[i].flip = false;
		if (state->enemies[i].velocity[0] != 0 && dir < 0)
			state->enemies[i].flip = true;
		vec2 offset;
		glm_vec2_zero(offset);
		if (state->enemies[i].flip)
			glm_vec2_copy((float*)CR_ENEMY_FLIP_OFFSETS[state->enemies[i].type], offset);
		CR_AppState_push_animated_sprite(
			state, &state->enemySprites[state->enemies[i].type][state->enemies[i].animation],
			(vec3){
				state->enemies[i].position[0] - offset[0] - CR_ENEMY_COLLISIONS[state->enemies[i].type].x,
				state->enemies[i].position[1] - offset[1] - CR_ENEMY_COLLISIONS[state->enemies[i].type].y,
				0.0f
			},
			(vec2){
				CR_ENEMY_WIDTH,
				CR_ENEMY_HEIGHT
			},
			(vec4){0.0f, 0.0f, 0.0f, 0.0f},
			state->enemies[i].flip,
			CR_ENEMY_ANIM_LENGTHS[state->enemies[i].type][state->enemies[i].animation],
			state->enemies[i].frameIndex
		);
	}
}
