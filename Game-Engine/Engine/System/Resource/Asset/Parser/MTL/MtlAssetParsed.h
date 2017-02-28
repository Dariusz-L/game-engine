#pragma once

#include "..\AssetParsed.h"

#include <vector>
#include <map>

#include "..\OBJ\TinyObj\TinyObjParserStructs.h"

struct MtlAssetParsed : AssetParsed {

	std::vector<TinyObj::material_t> tMaterials;
	std::map<std::string, int> map;
};