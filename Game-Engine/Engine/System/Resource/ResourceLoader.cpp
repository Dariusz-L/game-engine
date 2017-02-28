#include "ResourceLoader.h"

#include "..\..\Loader\FileLoader.h"
#include "..\Utility\String\StringUtility.h"

#include <vector>
#include <string>

using namespace Utility::String;

void ResourceLoader::ParseAllAssets() {
	FileLoader::ParseFileByLine("data/data.cfg",	
		[this]
		(std::string line) -> bool {

		line = RemoveSubstring(line, "\r");

		if (IfContainStr(line, "//"))			return true;

		std::vector<std::string> data			= Utility::String::Split(line, '=');

		if (data.size() == 0)					return true;

		if (_assetParsingManager.TryParse(line))return true;

		if (IfContainStr(line, "Components"))	return false;

		return true;
	});
}

void ResourceLoader::UnparseAllAssets() {
	_assetParsingManager.Unload();
}

AssetParsingManager* ResourceLoader::GetAssetParsingManager() {
	return &_assetParsingManager;
}

ResourceData* ResourceLoader::GetAllResources() {
	return &_resources;
}