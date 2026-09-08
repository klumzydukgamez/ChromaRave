#include "CR_shared.h"

void CR_AppState_quit(CR_AppState* state) {
	if (state->finalFramebuffer)
		glDeleteFramebuffers(1, &state->finalFramebuffer);
	if (state->finalTexture)
		glDeleteTextures(1, &state->finalTexture);
	if (state->finalShader)
		glDeleteProgram(state->finalShader);
	if (state->sceneShader)
		glDeleteProgram(state->sceneShader);
	if (state->masterTexture)
		glDeleteTextures(1, &state->masterTexture);
	if (state->dummyVertexArray)
		glDeleteVertexArrays(1, &state->dummyVertexArray);
	if (state->glContext)
		SDL_GL_DestroyContext(state->glContext);
	if (state->window)
		SDL_DestroyWindow(state->window);
	SDL_Quit();
}
