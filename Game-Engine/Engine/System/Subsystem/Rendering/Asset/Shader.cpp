#include "Shader.h"
#include <SDL.h>
#include "..\..\..\..\Loader\FileLoader.h"

#include "..\Utility\Uniform\UniformInfo.h"

#include <stdexcept>

Shader::Shader() :
	program(0) {}

void Shader::Load(std::vector<std::string>& filePaths) {
	Asset::Load(filePaths);

	const char* vCode = FileLoader::LoadFile(filePaths[0].c_str());
	const char* fCode = FileLoader::LoadFile(filePaths[1].c_str());

	GLuint vs;
	GLuint fs;
	GLint success;
	char infoLog[512];

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vCode, NULL);
	glCompileShader(vs);

	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		SDL_Log("ERROR::COMPILE::VERTEX::SHADER:  %s\n", infoLog);
	}

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fCode, NULL);
	glCompileShader(fs);

	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		SDL_Log("ERROR::COMPILE::FRAGMENT::SHADER:  %s\n", infoLog);
	}

	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(fs, 512, NULL, infoLog);
		SDL_Log("ERROR::LINKING::PROGRAM:  %s\n", infoLog);
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	int numActiveAttribs;
	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &numActiveAttribs);
	SDL_Log("active attribs: %d", numActiveAttribs);

	int count = 0;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
	uniformInfos.reserve(count);
	for (int i = 0; i < count; i++) {
		UniformInfo info;
		char buf[64];
		glGetActiveUniform(program, (GLuint) i, 64, &info.length, &info.size, &info.type, buf);
		info.name = buf;
		info.loc = glGetUniformLocation(program, info.name.c_str());

		try {
			uniformInfos.push_back({ UNIFORM_NAMES.at(info.name), info.loc });
		}
		catch (std::out_of_range e) {
			uniformInfos.push_back({ UniformType::NONE, info.loc });
		}
	}
}

void Shader::Use() {
	glUseProgram(program);
}

void Shader::Stop() {
	glUseProgram(0);
}

GLuint Shader::GetProgram() const {
	return program;
}

const std::vector<std::pair<UniformType, GLint>>* Shader::GetUniformInfos() {
	return &uniformInfos;
}