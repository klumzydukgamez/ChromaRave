#include "CR_shared.h"

float CR_random_shake_intensity() {
	return (SDL_randf() * 2.0f) - 1.0f;
}

void CR_AppState_shake_camera(CR_AppState* state, vec2 origin, vec2 direction, float radius, float intensity, float decay) {
	if (state->cameraShakeCount >= CR_MAX_CAMERA_SHAKES) {
		CR_PANIC("Camera Shakes Full.");
		return;
	}

	glm_vec2_copy(origin, state->cameraShakes[state->cameraShakeCount].origin);
	if (direction && glm_vec2_norm2(direction) > CR_MIN_CAMERA_SHAKE_DIRECTION)
		glm_vec2_copy(direction, state->cameraShakes[state->cameraShakeCount].direction);
	else
		glm_vec2_zero(state->cameraShakes[state->cameraShakeCount].direction);
	state->cameraShakes[state->cameraShakeCount].radius = radius;
	state->cameraShakes[state->cameraShakeCount].intensity = intensity;
	state->cameraShakes[state->cameraShakeCount].decay = decay;
	state->cameraShakeCount++;
}

void CR_AppState_update_camera(CR_AppState* state) {
	glm_vec2_lerp(
		state->cameraPosition, state->cameraTargetPosition,
		CR_CAMERA_MOVE_SPEED, state->cameraPosition
	);
	state->cameraZoom = glm_lerp(
		state->cameraZoom, state->cameraTargetZoom,
		CR_CAMERA_ZOOM_SPEED
	);

	vec2 shake;
	glm_vec2_zero(shake);
	for (int i = 0; i < state->cameraShakeCount; i++) {
		float distance = glm_vec2_distance(
			state->cameraPosition, state->cameraShakes[i].origin
		);
		if (distance < state->cameraShakes[i].radius) {
			float falloff = 1.0f - (distance / state->cameraShakes[i].radius);
			falloff = falloff * falloff;
			float maxIntensity = state->cameraShakes[i].intensity * falloff;
			float intensity = CR_random_shake_intensity() * maxIntensity;
			if (glm_vec2_norm2(state->cameraShakes[i].direction) > CR_MIN_CAMERA_SHAKE_DIRECTION) {
				shake[0] += state->cameraShakes[i].direction[0] * intensity;
				shake[1] += state->cameraShakes[i].direction[1] * intensity;
			} else {
				shake[0] += CR_random_shake_intensity() * maxIntensity;
				shake[1] += CR_random_shake_intensity() * maxIntensity;
			}
		}
		state->cameraShakes[i].intensity *= state->cameraShakes[i].decay;
		if (state->cameraShakes[i].intensity < CR_MIN_CAMERA_SHAKE_INTENSITY) {
			state->cameraShakes[i] = state->cameraShakes[state->cameraShakeCount - 1];
			state->cameraShakeCount--;
			i--;
		}
	}

	mat4 projection;
	glm_ortho(
		0.0f, (float)CR_WIDTH, (float)CR_HEIGHT,
		0.0f, CR_CAMERA_NEAR, CR_CAMERA_FAR, projection
	);
	mat4 view;
	glm_mat4_identity(view);
	glm_translate(
		view,
		(vec3){
			((float)CR_WIDTH / 2.0f),
			((float)CR_HEIGHT / 2.0f),
			0.0f
		}
	);
	glm_scale(view, (vec3){state->cameraZoom, state->cameraZoom, 1.0f});
	vec3 inverse = {
		-state->cameraPosition[0] + shake[0],
		-state->cameraPosition[1] + shake[1],
		0.0f
	};
	glm_translate(view, inverse);
	glm_mat4_mul(projection, view, state->cameraProjView);
}
