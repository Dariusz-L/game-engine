#pragma once

#include "..\AssetParsed.h"

#include <vector>

#include "..\OBJ\TinyObj\TinyObjLoaderStructs.h"

struct MtlAssetParsed : AssetParsed {

	std::vector<TinyObj::material_t> _tMaterials;

};