#include "CR_shared.h"

bool CR_AppState_iterate(CR_AppState* state) {
	glBindFramebuffer(GL_FRAMEBUFFER, state->finalFramebuffer);
	glViewport(0, 0, CR_WIDTH, CR_HEIGHT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CR_AppState_update_player(state);
	CR_AppState_update_camera(state);

	CR_AppState_draw_background(state);
	CR_AppState_draw_level(state);
	CR_AppState_draw_player(state);

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

	glViewport(state->viewport.x, state->viewport.y, state->viewport.w, state->viewport.h);
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

	CR_AppState_update_input(state);

	return true;
}
