#pragma once

#include "..\System\Config\Include\IncludeOpenGL.h"

#include <vector>

class Mesh;

class RenderingHelper
{
public:
	static void AddToGPU(std::vector<GLfloat>* vertices, std::vector<GLuint>* indices, Mesh* mesh, bool hasTangents);
};

