#if !defined __CR_UTILS_H__
#define __CR_UTILS_H__

#include "CR_common.h"

#define CR_PANIC(format, ...) \
	SDL_Log("[PANIC][%s][%d] " format, __FILE_NAME__, __LINE__, ##__VA_ARGS__)

#define CR_WARN(format, ...) \
	SDL_Log("[WARN][%s][%d] " format, __FILE_NAME__, __LINE__, ##__VA_ARGS__)

float CR_random_shake_intensity();

GLuint CR_compile_shader(const char* const vertSource, const char* const fragSource);

SDL_Surface* CR_load_surface(const Uint8* data, size_t size);
GLuint CR_create_texture(int width, int height, bool wrap, const void* pixels);
void CR_update_texture(GLuint texture, const SDL_Surface* surface, int x, int y);

#endif /* __CR_UTILS_H__ */
