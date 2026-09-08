#include "CR_shared.h"

void CR_AppState_update_camera(CR_AppState* state) {
	mat4 projection;
	glm_ortho(
		0.0f, (float)CR_WIDTH, (float)CR_HEIGHT, 0.0f,
		-1.0f, 1.0f, projection
	);
	mat4 view;
	glm_mat4_identity(view);
	vec3 inverse = {
		-state->cameraPosition[0],
		-state->cameraPosition[1],
		0.0f
	};
	glm_translate(view, inverse);
	glm_mat4_mul(projection, view, state->cameraProjView);
}
