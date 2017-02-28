#include "ShaderLoader.h"

#include "..\..\..\Config\Include\IncludeSDL.h"

#include "..\..\..\Resource\Asset\Parser\Shader\ShaderAssetParsed.h"
#include "..\Utility\Uniform\UniformInfo.h"
#include "..\Asset\Shader.h"

void ShaderLoader::Load(Shader* shader, AssetParsed* assetParsed) {

	GLuint vs;
	GLuint fs;
	GLint success;
	char infoLog[512];

	ShaderAssetParsed* shaderAssetParsed = static_cast<ShaderAssetParsed*>(assetParsed);

	const char* vCode = shaderAssetParsed->vertexCode.c_str();
	const char* fCode = shaderAssetParsed->fragmentCode.c_str();

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vCode, NULL);
	glCompileShader(vs);

	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		SDL_Log("ERROR::COMPILE::VERTEX::SHADER:  %s\n", infoLog);
	}

	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fCode, NULL);
	glCompileShader(fs);

	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		SDL_Log("ERROR::COMPILE::FRAGMENT::SHADER:  %s\n", infoLog);
	}

	shader->program = glCreateProgram();
	glAttachShader(shader->program, vs);
	glAttachShader(shader->program, fs);
	glLinkProgram(shader->program);

	glGetProgramiv(shader->program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(fs, 512, NULL, infoLog);
		SDL_Log("ERROR::LINKING::PROGRAM:  %s\n", infoLog);
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	int numActiveAttribs;
	glGetProgramiv(shader->program, GL_ACTIVE_ATTRIBUTES, &numActiveAttribs);

	int count = 0;
	glGetProgramiv(shader->program, GL_ACTIVE_UNIFORMS, &count);
	shader->uniformInfos.reserve(count);
	for (int i = 0; i < count; i++) {

		UniformInfo info;
		char buf[64];
		glGetActiveUniform(shader->program, (GLuint) i, 64, &info.length, &info.size, &info.type, buf);
		info.name = buf;
		info.loc = glGetUniformLocation(shader->program, info.name.c_str());

		try {
			shader->uniformInfos.push_back({ UNIFORM_NAMES.at(info.name), info.loc });
		}
		catch (std::out_of_range e) {
			shader->uniformInfos.push_back({ UniformType::NONE, info.loc });
		}
	}
}

void ShaderLoader::Destroy(Shader* shader) {
	shader->program = -1;
}