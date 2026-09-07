#include "CR_shared.h"

bool CR_AppState_init(CR_AppState* state) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		CR_PANIC("SDL_Init failed. %s", SDL_GetError());
		return false;
	}

	if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3)) {
		CR_PANIC("SDL_GL_SetAttribute failed. %s", SDL_GetError());
		return false;
	}
	if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3)) {
		CR_PANIC("SDL_GL_SetAttribute failed. %s", SDL_GetError());
		return false;
	}
	if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE)) {
		CR_PANIC("SDL_GL_SetAttribute failed. %s", SDL_GetError());
		return false;
	}

	state->window = SDL_CreateWindow(
		"Chroma Rave",
		CR_WIDTH, CR_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);
	if (!state->window) {
		CR_PANIC("SDL_CreateWindow failed. %s", SDL_GetError());
		return false;
	}

	state->glContext = SDL_GL_CreateContext(state->window);
	if (!state->glContext) {
		CR_PANIC("SDL_GL_CreateContext failed. %s", SDL_GetError());
		return false;
	}
	if (!SDL_GL_MakeCurrent(state->window, state->glContext)) {
		CR_PANIC("SDL_GL_MakeCurrent failed. %s", SDL_GetError());
		return false;
	}

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
		CR_PANIC("gladLoadGLLoader failed.");
		return false;
	}

	glGenVertexArrays(1, &state->dummyVertexArray);

	state->finalShader = CR_compile_shader(CR_asset_finalVert, CR_asset_finalFrag);
	if (!state->finalShader) {
		CR_PANIC("CR_compile_shader failed.");
		return false;
	}
	state->finalUniformTexture = glGetUniformLocation(state->finalShader, "uTexture");
	if (state->finalUniformTexture == -1) {
		CR_PANIC("[uTexture] glGetUniformLocation failed.");
		return false;
	}

	state->finalTexture = CR_create_texture(CR_WIDTH, CR_HEIGHT, false, nullptr);
	if (!state->finalTexture) {
		CR_PANIC("CR_create_texture failed.");
		return false;
	}
	SDL_Surface* defaultSurface = CR_load_surface(CR_asset_defaultPng, CR_asset_defaultPng_size);
	CR_update_texture(state->finalTexture, defaultSurface, 50, 50);

	glUseProgram(state->finalShader);
	glUniform1i(state->finalUniformTexture, 0);
	glUseProgram(0);

	glGenFramebuffers(1, &state->finalFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, state->finalFramebuffer);
	glFramebufferTexture2D(
		GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, state->finalTexture, 0
	);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		CR_PANIC("glFramebufferTexture2D failed.");
		return false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}
