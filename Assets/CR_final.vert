#version 330 core

out vec2 vTexCoords;

const vec2 gPositions[6] = vec2[](
	vec2(-1.0,  1.0),
	vec2(-1.0, -1.0),
	vec2( 1.0, -1.0),

	vec2(-1.0,  1.0),
	vec2( 1.0, -1.0),
	vec2( 1.0,  1.0)
);
const vec2 gTexCoords[6] = vec2[](
	vec2(0.0, 1.0),
	vec2(0.0, 0.0),
	vec2(1.0, 0.0),

	vec2(0.0, 1.0),
	vec2(1.0, 0.0),
	vec2(1.0, 1.0)
);

void main(void) {
	vTexCoords = gTexCoords[gl_VertexID];
	gl_Position = vec4(gPositions[gl_VertexID], 0.0, 1.0f);
}
