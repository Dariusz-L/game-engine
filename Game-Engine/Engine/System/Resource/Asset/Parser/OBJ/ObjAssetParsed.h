#pragma once

#include "..\AssetParsed.h"

#include "..\..\..\..\Config\Include\IncludeOpenGL.h"

#include "TinyObj\TinyObjLoaderStructs.h"

#include <vector>

struct ObjAssetParsed : AssetParsed {

	std::string						materiaFileName;
	TinyObj::attrib_t				attribs;
	std::vector<TinyObj::shape_t>	shapes;

};