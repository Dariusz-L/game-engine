#include "MeshAssetParser.h"

#include "..\AssetParsed.h"
#include "..\AssetToParse.h"
#include "MeshAssetParsed.h"

#include "TinyObj\TinyObjParser.h"
#include "..\..\..\..\..\Loader\FileLoader.h"
//#include "..\..\..\..\Config\Include\IncludeAssimp.h"

#include <sstream>

AssetParsed* MeshAssetParser::Parse(AssetToParse* assetToParse) {

	MeshAssetParsed* fileParsed = new MeshAssetParsed();

	std::stringstream stream(FileLoader::LoadFile(assetToParse->info[0].pathToFile));

	if (!TinyObj::LoadObj(
		&fileParsed->attribs, 
		&fileParsed->shapes, 
		fileParsed->materiaFileName,
		&stream))

		throw std::runtime_error("Parsing obj file error");

	return fileParsed;
}