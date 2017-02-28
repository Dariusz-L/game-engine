#include "ObjAssetParser.h"

#include "..\AssetParsed.h"
#include "..\AssetToParse.h"
#include "ObjAssetParsed.h"

#include "TinyObj\TinyObjLoader.h"
#include "..\..\..\..\..\Loader\FileLoader.h"
//#include "..\..\..\..\Config\Include\IncludeAssimp.h"

#include <sstream>

AssetParsed* ObjAssetParser::Parse(AssetToParse* assetToParse) {

	ObjAssetParsed* fileParsed = new ObjAssetParsed();

	std::stringstream stream(FileLoader::LoadFile(assetToParse->info[0].pathToFile));

	if (!TinyObj::LoadObj(
		&fileParsed->attribs, 
		&fileParsed->shapes, 
		fileParsed->materiaFileName,
		&stream))

		throw std::runtime_error("Parsing obj file error");

	return fileParsed;
}