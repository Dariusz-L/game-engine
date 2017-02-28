#pragma once

#include "..\..\..\..\Config\Include\IncludeOpenGL.h"

#include <string>

struct UniformInfo {

	GLuint index;
	GLsizei length;
	GLint size;
	GLenum type;
	std::string name;
	GLint loc;

};