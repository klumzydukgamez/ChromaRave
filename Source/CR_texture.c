#include "CR_shared.h"

SDL_Surface* CR_load_surface(const Uint8* data, size_t size) {
	SDL_IOStream* io = SDL_IOFromConstMem(data, size);
	if (!io) {
		CR_PANIC("SDL_IOFromConstMem failed. %s", SDL_GetError());
		return nullptr;
	}
	SDL_Surface* surface = SDL_LoadPNG_IO(io, true);
	if (!surface) {
		CR_PANIC("SDL_LoadPNG_IO failed. %s", SDL_GetError());
		return nullptr;
	}
	SDL_Surface* converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
	SDL_DestroySurface(surface);
	if (!converted) {
		CR_PANIC("SDL_ConvertSurface failed. %s", SDL_GetError());
		return nullptr;
	}
	return converted;
}

GLuint CR_create_texture(int width, int height, bool wrap, const void* pixels) {
	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGB8,
		width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, pixels
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	if (wrap) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

void CR_update_texture(GLuint texture, const SDL_Surface* surface, int x, int y) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexSubImage2D(
		GL_TEXTURE_2D, 0, x, y, surface->w, surface->h,
		GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels
	);
	glBindTexture(GL_TEXTURE_2D, 0);
}
