#include "CR_shared.h"

void CR_AppState_push_vertex(CR_AppState* state, const vec3 position, const vec2 texCoord, const vec4 color) {
	if (state->vertexCount >= CR_MAX_VERTICES) {
		CR_WARN("Vertices Full. Flushing.");
		CR_AppState_flush_vertices(state, false);
	}

	glm_vec3_copy((float*)position, state->vertices[state->vertexCount].position);
	glm_vec2_copy((float*)texCoord, state->vertices[state->vertexCount].texCoord);
	glm_vec4_copy((float*)color, state->vertices[state->vertexCount].color);

	state->vertexCount++;
}

void CR_AppState_push_sprite(CR_AppState* state, const SDL_FRect* sprite, const vec3 position, const vec2 size, const vec4 color, bool flip) {
	float uvLeft = sprite->x;
	float uvRight = sprite->x + sprite->w;
	if (flip) {
		uvLeft = sprite->x + sprite->w;
		uvRight = sprite->x;
	}
	CR_AppState_push_vertex(
		state,
		(vec3){
			position[0], position[1], position[2]
		},
		(vec2){
			uvLeft, sprite->y
		},
		color
	);
	CR_AppState_push_vertex(
		state,
		(vec3){
			position[0] + size[0], position[1], position[2]
		},
		(vec2){
			uvRight, sprite->y
		},
		color
	);
	CR_AppState_push_vertex(
		state,
		(vec3){
			position[0] + size[0], position[1] + size[1], position[2]
		},
		(vec2){
			uvRight, sprite->y + sprite->h
		},
		color
	);
	CR_AppState_push_vertex(
		state,
		(vec3){
			position[0], position[1] + size[1], position[2]
		},
		(vec2){
			uvLeft, sprite->y + sprite->h
		},
		color
	);
}

void CR_AppState_push_animated_sprite(CR_AppState* state, const SDL_FRect* sprite, const vec3 position, const vec2 size, const vec4 color, bool flip, int length, int frame) {
	if (length < 1)
		length = 1;
	float w = sprite->w / (float)length;
	float x = sprite->x + (frame * w);
	float uvLeft = x;
	float uvRight = x + w;
	if (flip) {
		uvLeft = x + w;
		uvRight = x;
	}
	CR_AppState_push_vertex(
		state,
		(vec3){
			position[0], position[1], position[2]
		},
		(vec2){
			uvLeft, sprite->y
		},
		color
	);
	CR_AppState_push_vertex(
		state,
		(vec3){
			position[0] + size[0], position[1], position[2]
		},
		(vec2){
			uvRight, sprite->y
		},
		color
	);
	CR_AppState_push_vertex(
		state,
		(vec3){
			position[0] + size[0], position[1] + size[1], position[2]
		},
		(vec2){
			uvRight, sprite->y + sprite->h
		},
		color
	);
	CR_AppState_push_vertex(
		state,
		(vec3){
			position[0], position[1] + size[1], position[2]
		},
		(vec2){
			uvLeft, sprite->y + sprite->h
		},
		color
	);
}

void CR_AppState_flush_vertices(CR_AppState* state, bool ui) {
	if (state->vertexCount == 0)
		return;

	glUseProgram(state->sceneShader);
	if (ui)
		glUniformMatrix4fv(state->sceneUniformProjView, 1, GL_FALSE, (const GLfloat*)state->uiProjView);
	else
		glUniformMatrix4fv(state->sceneUniformProjView, 1, GL_FALSE, (const GLfloat*)state->cameraProjView);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, state->masterTexture);
	glBindVertexArray(state->sceneVertexArray);
	glBufferData(
		GL_ARRAY_BUFFER, sizeof(state->vertices[0]) * CR_MAX_VERTICES,
		nullptr, GL_DYNAMIC_DRAW
	);
	glBufferSubData(
		GL_ARRAY_BUFFER, 0, sizeof(state->vertices[0]) * state->vertexCount,
		state->vertices
	);
	glDrawElements(
		GL_TRIANGLES, (GLsizei)((state->vertexCount / 4) * 6),
		GL_UNSIGNED_INT, nullptr
	);
	glBindVertexArray(0);
	state->vertexCount = 0;
}
