#version 330 core

in vec2 vTexCoord;
in vec4 vColor;

uniform sampler2D uTexture;

out vec4 oColor;

void main(void) {
	vec4 texColor = texture(uTexture, vTexCoord);
	if (texColor.a < 0.01) {
		discard;
	}
	vec3 tint = clamp(texColor.rgb + vColor.rgb, 0.0, 1.0);
	vec3 final = mix(texColor.rgb, tint, vColor.a);
	oColor = vec4(final, texColor.a);
}
