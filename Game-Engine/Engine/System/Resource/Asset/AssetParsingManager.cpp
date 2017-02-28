#include "AssetParsingManager.h"

#include "Parser\OBJ\MeshAssetParser.h"
#include "Parser\OBJ\MeshAssetParsed.h"
#include "Parser\Shader\ShaderAssetParser.h"
#include "Parser\Shader\ShaderAssetParsed.h"
#include "Parser\Image\ImageAssetParser.h"
#include "Parser\Image\ImageAssetParsed.h"
#include "Parser\MTL\MtlAssetParser.h"
#include "Parser\MTL\MtlAssetParsed.h"

#include "Parser\AssetToParse.h"
#include "..\..\..\Loader\FileLoader.h"
#include "..\..\Utility\String\StringUtility.h"

using namespace std;
using namespace Utility::String;

const std::string AssetParsingManager::BASE_PATH("data/");

AssetParsingManager::AssetParsingManager() {
	_parsers.push_back(new MeshAssetParser());
	_parsers.push_back(new ShaderAssetParser());
	_parsers.push_back(new ImageAssetParser());
	_parsers.push_back(new MtlAssetParser());
}

AssetParsingManager::~AssetParsingManager() {
	for (auto p : _parsers) {
		delete p;
	}
}

bool AssetParsingManager::TryParse(const std::string& line) {
	if (IfContainStr(line, "RObjModels")) {
		LoadAssets<MeshAssetParser, MeshAssetParsed>("objModels");
		return true;
	}

	if (IfContainStr(line, "RShaders")) {
		LoadAssets<ShaderAssetParser, ShaderAssetParsed>("shaders", 2);
		return true;
	}

	if (IfContainStr(line, "RTextures")) {
		LoadAssets<ImageAssetParser, ImageAssetParsed>("textures");
		return true;
	}

	if (IfContainStr(line, "RMtlMaterials")) {
		LoadAssets<MtlAssetParser, MtlAssetParsed>("materials");
		return true;
	}

	return false;
}

void AssetParsingManager::Unload() {

	for (auto a1 : _assetsParsed) {
		for (auto a2 : *a1.second) {
			delete a2;
		}

		delete a1.second;
	}

	_assetsParsed.clear();
}

AssetsParsed* AssetParsingManager::GetAssetsParsed() {
	return &_assetsParsed;
}