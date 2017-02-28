#pragma once

#include "..\..\..\Config\Include\IncludeOpenGL.h"
#include "..\..\..\Resource\Asset\Asset.h"
#include "..\RenderingConfig.h"

#include <string>
#include <vector>
#include <unordered_map>

class Shader: public Asset {

public:
	std::vector<std::pair<UniformType, GLint>> uniformInfos;
	GLuint program;
	Shader();

	void Load(std::vector<std::string>& filePaths) override;

	void Use();
	void Stop();

	GLuint GetProgram() const;

	const std::vector<std::pair<UniformType, GLint>>* GetUniformInfos();

};
