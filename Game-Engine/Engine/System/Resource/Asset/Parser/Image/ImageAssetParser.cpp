#include "ImageAssetParser.h"

#include "..\..\..\..\Config\Include\IncludeSDL.h"
#include "..\AssetToParse.h"
#include "..\..\..\..\..\Loader\FileLoader.h"
#include "ImageAssetParsed.h"

AssetParsed* ImageAssetParser::Parse(AssetToParse* fileToParse) {

	ImageAssetParsed* textureAssetParsed = new ImageAssetParsed();

	textureAssetParsed->surface = FileLoader::LoadImageFile(fileToParse->info[0].pathToFile);

	return textureAssetParsed;
}