#version 330 core

in vec2 vTexCoords;

out vec4 oColor;

uniform sampler2D uTexture;

void main(void) {
	oColor = texture(uTexture, vTexCoords);
}
