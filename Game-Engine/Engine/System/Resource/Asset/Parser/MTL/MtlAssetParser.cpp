#include "MtlAssetParser.h"

#include "MtlAssetParsed.h"
#include "..\AssetToParse.h"
#include "..\OBJ\TinyObj\TinyObjLoader.h"
#include "..\..\..\..\..\Loader\FileLoader.h"

#include <map>
#include <string>
#include <sstream>

AssetParsed* MtlAssetParser::Parse(AssetToParse* fileToParse) {

	MtlAssetParsed* mtlAssetParsed = new MtlAssetParsed();

	std::map<std::string, int> map;
	std::stringstream stream(FileLoader::LoadFile(fileToParse->info[0].pathToFile));

	TinyObj::LoadMtl(&map, &mtlAssetParsed->_tMaterials, &stream);

	return mtlAssetParsed;
}