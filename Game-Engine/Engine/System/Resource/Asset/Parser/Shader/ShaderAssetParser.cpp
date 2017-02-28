#include "ShaderAssetParser.h"

#include "ShaderAssetParsed.h"
#include "..\AssetToParse.h"
#include "..\..\..\..\..\Loader\FileLoader.h"

AssetParsed* ShaderAssetParser::Parse(AssetToParse* assetToParse) {

	ShaderAssetParsed* shaderAssetParsed = new ShaderAssetParsed();

	shaderAssetParsed->vertexCode = FileLoader::LoadFile(assetToParse->info[0].pathToFile);
	shaderAssetParsed->fragmentCode = FileLoader::LoadFile(assetToParse->info[1].pathToFile);

	return shaderAssetParsed;
}