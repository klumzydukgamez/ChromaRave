#include "CR_shared.h"

bool CR_AppState_iterate(CR_AppState* state) {
	CR_AppState_update_camera(state);

	glBindFramebuffer(GL_FRAMEBUFFER, state->finalFramebuffer);
	glViewport(0, 0, CR_WIDTH, CR_HEIGHT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CR_AppState_push_sprite(
		state, &state->defaultSprite,
		(vec3){100.0f, 100.0f, 0.0f},
		(vec2){96.0f, 96.0f},
		(vec4){1.0f, 0.0f, 0.0f, fabs(sin(SDL_GetTicks() * 0.01))}
	);
	CR_AppState_push_sprite(
		state, &state->defaultSprite,
		(vec3){200.0f, 200.0f, 0.0f},
		(vec2){96.0f, 96.0f},
		(vec4){1.0f, 0.0f, 0.0f, 0.0f}
	);

	CR_AppState_flush_vertices(state);
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

	return true;
}
