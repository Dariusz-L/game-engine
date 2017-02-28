#pragma once

#include "Parser\AssetParser.h"
#include "Parser\AssetParsed.h"
#include "Parser\AssetInfo.h"
#include "Parser\AssetToParse.h"

#include "..\..\Utility\String\StringUtility.h"
#include "..\..\..\Loader\FileLoader.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <typeindex>

class ObjAssetParsed;

using AssetsParsed = std::unordered_map<std::type_index, std::vector<AssetParsed*>*>;

class AssetParsingManager
{
private:
	static const std::string BASE_PATH;

	std::vector<AssetParser*> _parsers;
	AssetsParsed _assetsParsed;

public:
	AssetParsingManager();
	~AssetParsingManager();
	bool TryParse(const std::string& line);
	void Unload();
	AssetsParsed* GetAssetsParsed();

	template<class T>
	T* GetParser() {
		for (auto p : _parsers) 
			if (typeid(*p) == typeid(T))
				return static_cast<T*>(p);

		return nullptr;
	}

	template<class T1, class T2>
	bool LoadAssets (const std::string& folderName, int filesPerAsset = 1) {
		using namespace std;
		using namespace Utility::String;

		auto newAssets = new std::vector<AssetParsed*>();

		vector<string> assetsNames = Split(FileLoader::LoadFile(BASE_PATH + folderName + "/" + folderName + ".cfg"), '\n');
		for (int i = 0; i < assetsNames.size(); i += filesPerAsset) {

			AssetToParse assetToParse;
			for (int j = 0; j < filesPerAsset; j++) {
				std::string line = assetsNames[i + j];
				line = RemoveSubstring(line, "\r");

				AssetInfo assetInfo;
				assetInfo.pathToFile = BASE_PATH + folderName + "/" + line;
				vector<string> fileName = Split(line, '.');
				assetInfo.name = fileName[0];
				assetInfo.format = fileName[1];
				assetToParse.info.push_back(assetInfo);
			}

			AssetParsed* parsed = GetParser<T1>()->Parse(&assetToParse);
			parsed->name = assetToParse.info[0].name;
			newAssets->push_back(parsed);
		}

		_assetsParsed.emplace(typeid(T1), newAssets);
		return true;
	}

	template<class T>
	T* GetAssetByFileName(const std::string& fileName) {
		std::vector<AssetParsed*>* assetGroup = nullptr;

		try {
			assetGroup = _assetsParsed.at(typeid(T));
		} catch (std::out_of_range e) {
			return nullptr;
		}

		for (auto a : *assetGroup) {
			if (a->name == fileName)
				return a;
		}

		return nullptr;
	}
};

