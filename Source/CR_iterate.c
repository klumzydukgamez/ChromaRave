#include "CR_shared.h"

bool CR_AppState_iterate(CR_AppState* state) {
	glBindFramebuffer(GL_FRAMEBUFFER, state->finalFramebuffer);
	glViewport(0, 0, CR_WIDTH, CR_HEIGHT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (state->timeScale != state->targetTimeScale) {
		state->timeScale = glm_lerp(
			state->timeScale, state->targetTimeScale,
			CR_TIME_SCALE_CHANGE_SPEED
		);
		if (SDL_fabs(state->timeScale - state->targetTimeScale) < CR_TIME_SCALE_TOLERANCE)
			state->timeScale = state->targetTimeScale;
	}

	Uint64 counter = SDL_GetPerformanceCounter();
	Uint64 frequency = SDL_GetPerformanceFrequency();
	double elapsed = (double)(counter - state->lastTime) / (double)frequency;
	state->lastTime = counter;
	if (elapsed > CR_MAX_ELAPSED)
		elapsed = CR_MAX_ELAPSED;
	elapsed *= state->timeScale;
	state->time += elapsed * 1000.0;
	state->ticks = (Uint64)(state->time);
	state->accumulator += elapsed;

	while (state->accumulator >= CR_FRAME_TIME) {
		if (CR_AppState_keyboard_pressed(state, CR_GOD_MODE) && CR_ALLOW_GOD_MODE) {
			state->godMode = !state->godMode;
			if (state->godMode) {
				state->playerHealth = CR_MAX_PLAYER_HEALTH;
			}
			CR_INFO("God Mode. %d.", state->godMode);
		}

		if (state->godMode)
			CR_AppState_update_player_god_mode(state);
		else
			CR_AppState_update_player(state);
		CR_AppState_update_enemies(state);
		CR_AppState_update_camera(state);

		state->accumulator -= CR_FRAME_TIME;
		CR_AppState_update_input(state);
	}

	CR_AppState_draw_background(state);
	CR_AppState_draw_tiles(state);
	if (state->playerAlive) {
		CR_AppState_draw_enemies(state);
		if (state->godMode)
			CR_AppState_draw_player_god_mode(state);
		else
			CR_AppState_draw_player(state);
	} else {
		if (state->godMode)
			CR_AppState_draw_player_god_mode(state);
		else
			CR_AppState_draw_player(state);
		CR_AppState_draw_enemies(state);
	}

	CR_AppState_flush_vertices(state, false);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	int w, h;
	if (!SDL_GetWindowSizeInPixels(state->window, &w, &h)) {
		CR_PANIC("SDL_GetWindowSizeInPixels failed. %s", SDL_GetError());
		return false;
	}
	glViewport(0, 0, w, h);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(
		state->viewport.x + (state->viewport.w - (state->viewport.w * state->cameraZoom)) / 2,
		state->viewport.y + (state->viewport.h - (state->viewport.h * state->cameraZoom)) / 2,
		state->viewport.w * state->cameraZoom,
		state->viewport.h * state->cameraZoom
	);
	glUseProgram(state->finalShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, state->finalTexture);
	glBindVertexArray(state->dummyVertexArray);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	if (!SDL_GL_SwapWindow(state->window)) {
		CR_PANIC("SDL_GL_SwapWindow failed. %s", SDL_GetError());
		return false;
	}
	return true;
}
