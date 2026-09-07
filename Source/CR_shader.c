#include "CR_shared.h"

GLuint CR_compile_shader(const char* const vertSource, const char* const fragSource) {
	GLint success = 0;
	GLchar log[512] = {0};

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	if (!vertex) {
		CR_PANIC("[GL_VERTEX_SHADER] glCreateShader failed.");
		return 0;
	}
	glShaderSource(vertex, 1, &vertSource, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		CR_PANIC("[GL_VERTEX_SHADER] glCompileShader failed.");
		glGetShaderInfoLog(vertex, sizeof(log), nullptr, log);
		CR_PANIC("[GL_VERTEX_SHADER] %s", log);
		glDeleteShader(vertex);
		return 0;
	}

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	if (!fragment) {
		CR_PANIC("[GL_FRAGMENT_SHADER] glCreateShader failed.");
		return 0;
	}
	glShaderSource(fragment, 1, &fragSource, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		CR_PANIC("[GL_FRAGMENT_SHADER] glCompileShader failed.");
		glGetShaderInfoLog(fragment, sizeof(log), nullptr, log);
		CR_PANIC("[GL_FRAGMENT_SHADER] %s", log);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return 0;
	}

	GLuint program = glCreateProgram();
	if (!program) {
		CR_PANIC("glCreateProgram failed.");
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return 0;
	}
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	glDetachShader(program, vertex);
	glDetachShader(program, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		CR_PANIC("glLinkProgram failed.");
		glGetProgramInfoLog(program, sizeof(log), nullptr, log);
		glDeleteProgram(program);
		return 0;
	}
	return program;
}
