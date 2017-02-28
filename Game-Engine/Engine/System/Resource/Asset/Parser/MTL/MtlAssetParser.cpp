#include "MtlAssetParser.h"

#include "MtlAssetParsed.h"
#include "..\AssetToParse.h"
#include "..\OBJ\TinyObj\TinyObjParser.h"
#include "..\..\..\..\..\Loader\FileLoader.h"

#include <string>
#include <sstream>

AssetParsed* MtlAssetParser::Parse(AssetToParse* fileToParse) {

	MtlAssetParsed* mtlAssetParsed = new MtlAssetParsed();

	std::stringstream stream(FileLoader::LoadFile(fileToParse->info[0].pathToFile));

	TinyObj::LoadMtl(&mtlAssetParsed->map, &mtlAssetParsed->tMaterials, &stream);

	return mtlAssetParsed;
}