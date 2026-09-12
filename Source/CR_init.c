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

	/* if (!SDL_GL_SetSwapInterval(1)) {
		CR_PANIC("SDL_GL_SetSwapInterval failed. %s", SDL_GetError());
		return false;
	} */

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	state->lastTime = SDL_GetPerformanceCounter();
	state->accumulator = 0.0;
	state->timeScale = 1.0;
	state->targetTimeScale = 1.0;
	state->time = 0.0;
	state->ticks = 0;

	SDL_memset(&state->keyboardKeys, 0, sizeof(state->keyboardKeys));
	SDL_memset(&state->keyboardPreviousKeys, 0, sizeof(state->keyboardPreviousKeys));
	SDL_memset(&state->mouseButtons, 0, sizeof(state->mouseButtons));
	SDL_memset(&state->mousePreviousButtons, 0, sizeof(state->mousePreviousButtons));

	glGenVertexArrays(1, &state->dummyVertexArray);

	state->finalShader = CR_compile_shader(CR_asset_final_vert, CR_asset_final_frag);
	if (!state->finalShader) {
		CR_PANIC("CR_compile_shader failed.");
		return false;
	}
	state->finalUniformTexture = glGetUniformLocation(state->finalShader, "uTexture");
	if (state->finalUniformTexture == -1) {
		CR_PANIC("[uTexture] glGetUniformLocation failed.");
		return false;
	}
	state->finalTexture = CR_create_texture(CR_WIDTH, CR_HEIGHT, false, false, nullptr);
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

	SDL_memset(&state->vertices, 0, sizeof(state->vertices));
	state->vertexCount = 0;

	state->sceneShader = CR_compile_shader(CR_asset_scene_vert, CR_asset_scene_frag);
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

	glm_vec2_zero(state->cameraPosition);
	glm_vec2_zero(state->cameraTargetPosition);
	state->cameraZoom = 1.0f;
	state->cameraTargetZoom = 1.0f;
	SDL_srand(0);
	SDL_memset(&state->cameraShakes, 0, sizeof(state->cameraShakes));
	state->cameraShakeCount = 0;
	glm_mat4_identity(state->cameraProjView);

	state->masterTexture = CR_create_texture(CR_MASTER_TEX_WIDTH, CR_MASTER_TEX_HEIGHT, false, false, nullptr);
	if (!state->masterTexture) {
		CR_PANIC("CR_create_texture failed.");
		return false;
	}
	state->masterX = 0;
	state->masterY = 0;
	state->masterOffset = 0;

	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_default_png, CR_asset_default_png_size),
			&state->defaultSprite, true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}
	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_blank_png, CR_asset_blank_png_size),
			&state->blankSprite, true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}
	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_overlay_png, CR_asset_overlany_png_size),
			&state->overlaySprite, true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}

	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_background_1_png, CR_asset_background_1_png_size),
			&state->backgroundSprites[0], true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}
	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_background_2_png, CR_asset_background_2_png_size),
			&state->backgroundSprites[1], true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}
	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_background_3_png, CR_asset_background_3_png_size),
			&state->backgroundSprites[2], true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}
	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_background_4_png, CR_asset_background_4_png_size),
			&state->backgroundSprites[3], true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}
	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_background_5_png, CR_asset_background_5_png_size),
			&state->backgroundSprites[4], true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}

	CR_PACK_TILE(1);
	CR_PACK_TILE(2);
	CR_PACK_TILE(3);
	CR_PACK_TILE(4);
	CR_PACK_TILE(5);
	CR_PACK_TILE(6);
	CR_PACK_TILE(7);
	CR_PACK_TILE(8);
	CR_PACK_TILE(9);
	CR_PACK_TILE(10);
	CR_PACK_TILE(11);
	CR_PACK_TILE(12);
	CR_PACK_TILE(13);
	CR_PACK_TILE(14);
	CR_PACK_TILE(15);
	CR_PACK_TILE(16);
	CR_PACK_TILE(17);
	CR_PACK_TILE(18);
	CR_PACK_TILE(19);
	CR_PACK_TILE(20);
	CR_PACK_TILE(21);
	CR_PACK_TILE(22);
	CR_PACK_TILE(23);
	CR_PACK_TILE(24);
	CR_PACK_TILE(25);
	CR_PACK_TILE(26);
	CR_PACK_TILE(27);
	CR_PACK_TILE(28);
	CR_PACK_TILE(29);
	CR_PACK_TILE(30);
	CR_PACK_TILE(31);
	CR_PACK_TILE(32);
	CR_PACK_TILE(33);
	CR_PACK_TILE(34);
	CR_PACK_TILE(35);
	CR_PACK_TILE(36);
	CR_PACK_TILE(37);
	CR_PACK_TILE(38);
	CR_PACK_TILE(39);
	CR_PACK_TILE(40);
	CR_PACK_TILE(41);
	CR_PACK_TILE(42);
	CR_PACK_TILE(43);
	CR_PACK_TILE(44);
	CR_PACK_TILE(45);
	CR_PACK_TILE(46);
	CR_PACK_TILE(47);
	CR_PACK_TILE(48);
	CR_PACK_TILE(49);
	CR_PACK_TILE(50);
	CR_PACK_TILE(51);
	CR_PACK_TILE(52);
	CR_PACK_TILE(53);
	CR_PACK_TILE(54);
	CR_PACK_TILE(55);
	CR_PACK_TILE(56);
	CR_PACK_TILE(57);
	CR_PACK_TILE(58);
	CR_PACK_TILE(59);
	CR_PACK_TILE(60);
	CR_PACK_TILE(61);
	CR_PACK_TILE(62);
	CR_PACK_TILE(63);
	CR_PACK_TILE(64);
	CR_PACK_TILE(65);
	CR_PACK_TILE(66);
	CR_PACK_TILE(67);
	CR_PACK_TILE(68);
	CR_PACK_TILE(69);
	CR_PACK_TILE(70);
	CR_PACK_TILE(71);
	CR_PACK_TILE(72);
	CR_PACK_TILE(73);
	CR_PACK_TILE(74);
	CR_PACK_TILE(75);
	CR_PACK_TILE(76);
	CR_PACK_TILE(77);
	CR_PACK_TILE(78);
	CR_PACK_TILE(79);
	CR_PACK_TILE(80);
	CR_PACK_TILE(81);
	CR_PACK_TILE(82);
	CR_PACK_TILE(83);
	CR_PACK_TILE(84);
	CR_PACK_TILE(85);
	CR_PACK_TILE(86);
	CR_PACK_TILE(87);
	CR_PACK_TILE(88);
	CR_PACK_TILE(89);
	CR_PACK_TILE(90);
	CR_PACK_TILE(91);
	CR_PACK_TILE(92);
	CR_PACK_TILE(93);
	CR_PACK_TILE(94);
	CR_PACK_TILE(95);
	CR_PACK_TILE(96);
	CR_PACK_TILE(97);
	CR_PACK_TILE(98);
	CR_PACK_TILE(99);
	CR_PACK_TILE(100);
	CR_PACK_TILE(101);
	CR_PACK_TILE(102);
	CR_PACK_TILE(103);
	CR_PACK_TILE(104);
	CR_PACK_TILE(105);
	CR_PACK_TILE(106);
	CR_PACK_TILE(107);
	CR_PACK_TILE(108);
	CR_PACK_TILE(109);
	CR_PACK_TILE(110);
	CR_PACK_TILE(111);
	CR_PACK_TILE(112);
	CR_PACK_TILE(113);
	CR_PACK_TILE(114);
	CR_PACK_TILE(115);
	CR_PACK_TILE(116);
	CR_PACK_TILE(117);
	CR_PACK_TILE(118);
	CR_PACK_TILE(119);
	CR_PACK_TILE(120);
	CR_PACK_TILE(121);
	CR_PACK_TILE(122);
	CR_PACK_TILE(123);
	CR_PACK_TILE(124);
	CR_PACK_TILE(125);
	CR_PACK_TILE(126);

	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_enemy_baton_warden_idle_png, CR_asset_enemy_baton_warden_idle_png_size),
			&state->enemySprites[CR_EEnemyType_BATON_WARDEN][CR_EEnemyAnim_IDLE], true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}
	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_enemy_baton_warden_walk_png, CR_asset_enemy_baton_warden_walk_png_size),
			&state->enemySprites[CR_EEnemyType_BATON_WARDEN][CR_EEnemyAnim_WALK], true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}

	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_player_god_mode_png, CR_asset_player_god_mode_png_size),
			&state->playerSprites[CR_EPlayerAnim_GOD_MODE], true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}
	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_player_idle_png, CR_asset_player_idle_png_size),
			&state->playerSprites[CR_EPlayerAnim_IDLE], true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}
	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_player_run_png, CR_asset_player_run_png_size),
			&state->playerSprites[CR_EPlayerAnim_RUN], true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}
	if (!CR_AppState_pack_surface(
			state,
			CR_load_surface(CR_asset_player_jump_png, CR_asset_player_jump_png_size),
			&state->playerSprites[CR_EPlayerAnim_JUMP], true
		)) {
		CR_PANIC("CR_AppState_pack_surface failed.");
		return false;
	}

	SDL_memset(&state->tiles, 0, sizeof(state->tiles));

	SDL_memset(state->enemies, 0, sizeof(state->enemies));

	if (!CR_AppState_load_level(
			state,
			CR_load_surface(CR_asset_level_png, CR_asset_level_png_size),
			true
		)) {
		CR_PANIC("CR_AppState_load_level failed.");
		return false;
	}

	state->godMode = false;
	state->godModeBoost = false;

	glm_vec2_zero(state->playerVelocity);
	state->playerOnGround = false;
	state->playerLastGroundTick = 0;
	state->playerAnimation = CR_EPlayerAnim_IDLE;
	state->playerLastAnimation = CR_EPlayerAnim_IDLE;
	state->playerFrameIndex = 0;
	state->playerLastFrameTick = state->ticks;
	state->playerPlaying = true;
	state->playerFlip = false;
	state->playerEnemyThreat = 0.0;

	return true;
}
