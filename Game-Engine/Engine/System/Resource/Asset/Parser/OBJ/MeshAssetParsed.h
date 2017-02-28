#pragma once

#include "..\AssetParsed.h"
#include "..\..\..\..\Config\Include\IncludeOpenGL.h"
#include "TinyObj\TinyObjParserStructs.h"
#include <vector>

struct MeshAssetParsed : AssetParsed {

	std::string						materiaFileName;
	TinyObj::attrib_t				attribs;
	std::vector<TinyObj::shape_t>	shapes;

};