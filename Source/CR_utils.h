#if !defined __CR_UTILS_H__
#define __CR_UTILS_H__

#include "CR_common.h"

#if !defined CR_RELEASE
#define CR_PANIC(format, ...) \
	SDL_Log("[PANIC][%s][%d] " format, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define CR_WARN(format, ...) \
	SDL_Log("[WARN][%s][%d] " format, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#define CR_INFO(format, ...) \
	SDL_Log("[INFO][%s][%d] " format, __FILE_NAME__, __LINE__, ##__VA_ARGS__)
#else
#define CR_PANIC
#define CR_WARN
#define CR_INFO
#endif

#define CR_TILE_ASSET_HEADER(tile)                        \
	extern const Uint8* const CR_asset_tile_##tile##_png; \
	extern const size_t CR_asset_tile_##tile##_png_size;
#define CR_PACK_TILE(tile)                                                                \
	if (!CR_AppState_pack_surface(                                                        \
			state,                                                                        \
			CR_load_surface(CR_asset_tile_##tile##_png, CR_asset_tile_##tile##_png_size), \
			&state->tileSprites[tile], true                                               \
		)) {                                                                              \
		CR_PANIC("CR_AppState_pack_surface failed.");                                     \
		return false;                                                                     \
	}

float CR_random_shake_intensity();

GLuint CR_compile_shader(const char* const vertSource, const char* const fragSource);

SDL_Surface* CR_load_surface(const Uint8* data, size_t size);
GLuint CR_create_texture(int width, int height, bool wrap, bool linear, const void* pixels);
void CR_update_texture(GLuint texture, const SDL_Surface* surface, int x, int y);

#endif /* __CR_UTILS_H__ */
