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

GLuint CR_create_texture(int width, int height, bool wrap, bool linear, const void* pixels) {
	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA8,
		width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, pixels
	);
	if (linear) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	if (wrap) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	return texture;
}

void CR_update_texture(GLuint texture, const SDL_Surface* surface, int x, int y) {
	if (!surface) {
		CR_PANIC("Null Surface.");
		return;
	}

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexSubImage2D(
		GL_TEXTURE_2D, 0, x, y, surface->w, surface->h,
		GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels
	);
}

bool CR_AppState_pack_surface(CR_AppState* state, SDL_Surface* surface, SDL_FRect* sprite, bool cleanup) {
	if (!surface) {
		CR_PANIC("Null Surface.");
		return false;
	}

	if (surface->w + (CR_MASTER_TEX_PADDING * 2) > CR_MASTER_TEX_WIDTH || surface->h + (CR_MASTER_TEX_PADDING * 2) > CR_MASTER_TEX_HEIGHT) {
		CR_PANIC("Surface Too Large.");
		if (cleanup)
			SDL_DestroySurface(surface);
		return false;
	}

	if (state->masterX + surface->w + (CR_MASTER_TEX_PADDING * 2) > CR_MASTER_TEX_WIDTH) {
		state->masterY += state->masterOffset;
		state->masterX = 0;
		state->masterOffset = 0;
	}
	if (state->masterY + surface->h + (CR_MASTER_TEX_PADDING * 2) > CR_MASTER_TEX_HEIGHT) {
		CR_PANIC("Master Full.");
		if (cleanup)
			SDL_DestroySurface(surface);
		return false;
	}

	CR_update_texture(state->masterTexture, surface, state->masterX + CR_MASTER_TEX_PADDING, state->masterY + CR_MASTER_TEX_PADDING);

	if (sprite) {
		sprite->x = (float)(state->masterX + CR_MASTER_TEX_PADDING) / (float)CR_MASTER_TEX_WIDTH;

		sprite->y = (float)(state->masterY + CR_MASTER_TEX_PADDING) / (float)CR_MASTER_TEX_HEIGHT;
		sprite->w = (float)surface->w / (float)CR_MASTER_TEX_WIDTH;
		sprite->h = (float)surface->h / (float)CR_MASTER_TEX_HEIGHT;
	}

	state->masterX += surface->w + (CR_MASTER_TEX_PADDING * 2);
	if (surface->h + (CR_MASTER_TEX_PADDING * 2) > state->masterOffset)
		state->masterOffset = surface->h + (CR_MASTER_TEX_PADDING * 2);

	if (cleanup)
		SDL_DestroySurface(surface);

	return true;
}
