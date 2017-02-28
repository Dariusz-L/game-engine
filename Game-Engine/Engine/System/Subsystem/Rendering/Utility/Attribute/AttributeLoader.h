#pragma once

#include "..\..\..\..\Config\Include\IncludeOpenGL.h"

#include <vector>

class Mesh;

class AttributeLoader
{
public:
	
	static void Load(Mesh* mesh, std::vector<GLfloat>* data, std::vector<GLuint>* indices);
};

