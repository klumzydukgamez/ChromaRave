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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm_vec2_zero(state->cameraPosition);
	glm_mat4_identity(state->cameraProjView);

	glGenVertexArrays(1, &state->dummyVertexArray);

	state->masterTexture = CR_create_texture(CR_MASTER_TEX_WIDTH, CR_MASTER_TEX_HEIGHT, false, nullptr);
	if (!state->masterTexture) {
		CR_PANIC("CR_create_texture failed.");
		return false;
	}
	state->masterX = 0;
	state->masterY = 0;
	state->masterOffset = 0;

	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_defaultPng, CR_asset_defaultPng_size),
			&state->defaultSprite, true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}

	state->sceneShader = CR_compile_shader(CR_asset_sceneVert, CR_asset_sceneFrag);
	if (!state->sceneShader) {
		CR_PANIC("CR_compile_shader failed.");
		return false;
	}
	state->sceneUniformProjView = glGetUniformLocation(state->sceneShader, "uProjView");
	if (state->sceneUniformProjView == -1) {
		CR_PANIC("[uProjView] glGetUniformLocation failed.");
		return false;
	}
	state->sceneUniformTexture = glGetUniformLocation(state->sceneShader, "uTexture");
	if (state->sceneUniformTexture == -1) {
		CR_PANIC("[uTexture] glGetUniformLocation failed.");
		return false;
	}
	glUseProgram(state->sceneShader);
	glUniform1i(state->sceneUniformTexture, 0);

	SDL_memset(&state->vertices, 0, sizeof(state->vertices));
	state->vertexCount = 0;

	glGenVertexArrays(1, &state->sceneVertexArray);
	glGenBuffers(1, &state->sceneVertexBuffer);
	glGenBuffers(1, &state->sceneElementBuffer);
	glBindVertexArray(state->sceneVertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, state->sceneVertexBuffer);
	glBufferData(
		GL_ARRAY_BUFFER, sizeof(state->vertices[0]) * CR_MAX_VERTICES,
		nullptr, GL_DYNAMIC_DRAW
	);
	Uint32 indices[CR_MAX_INDICES];
	Uint32 indexOffset = 0;
	for (Uint32 i = 0; i < CR_MAX_INDICES; i += 6) {
		indices[i + 0] = indexOffset + 0;
		indices[i + 1] = indexOffset + 1;
		indices[i + 2] = indexOffset + 2;
		indices[i + 3] = indexOffset + 2;
		indices[i + 4] = indexOffset + 3;
		indices[i + 5] = indexOffset + 0;
		indexOffset += 4;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state->sceneElementBuffer);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
		indices, GL_STATIC_DRAW
	);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0, 3, GL_FLOAT, GL_FALSE, sizeof(state->vertices[0]),
		(const void*)offsetof(typeof(state->vertices[0]), position)
	);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1, 2, GL_FLOAT, GL_FALSE, sizeof(state->vertices[0]),
		(const void*)offsetof(typeof(state->vertices[0]), texCoord)
	);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2, 4, GL_FLOAT, GL_FALSE, sizeof(state->vertices[0]),
		(const void*)offsetof(typeof(state->vertices[0]), color)
	);
	glBindVertexArray(0);

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
	glUseProgram(state->finalShader);
	glUniform1i(state->finalUniformTexture, 0);

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
