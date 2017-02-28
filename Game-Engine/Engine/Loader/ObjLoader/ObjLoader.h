#pragma once

#include "..\..\System\Resource\Asset\Parser\OBJ\TinyObj\TinyObjParser.h"
#include "..\..\System\Config\Include\IncludeOpenGL.h"

#include <vector>

class Material;
class ObjModel;

class ObjLoader
{
public:
	static bool SetMaterial(ObjModel* owner, TinyObj::shape_t* shape, std::vector<Material*>* materials);
	static void SetVertices(TinyObj::shape_t& shape, TinyObj::attrib_t& attrib, std::vector<GLfloat>& vertices, std::vector<GLuint>& indices, bool hasNormalMap);
};