#pragma once

#include "..\..\..\..\Config\Include\IncludeOpenGL.h"

#include "..\..\Utility\Attribute\AttributeInfo.h"

#include <vector>

class Mesh
{

public:

	~Mesh();
	void ClearVBO();

	GLuint vao;
	GLuint vbo;
	GLuint ebo;

	std::vector<GLfloat> vertexData;
	std::vector<GLuint>  indices;
	
	int	dataSize;
	int	indicesSize;

	AttributesInfo attribs;

};