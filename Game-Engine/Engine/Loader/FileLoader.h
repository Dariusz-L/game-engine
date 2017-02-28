#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <utility>
#include <sstream>
#include "..\System\Config\Include\IncludeSDL.h"
#include "..\System\Resource\Asset\Parser\OBJ\TinyObj\TinyObjLoader.h"

class ObjModel;

class FileLoader
{
public:
	static const std::string DATA_CFG_PATH;

	static std::string GetFileName(const std::string& filePath);
	static void ParseFileByLine(const std::string& filePath, std::function<bool(const std::string& line)> f);
	static char* LoadFile(const std::string& filePath, Sint64* size = nullptr);
	static void WriteFile(const std::string& filePath, const std::string& data, size_t size);
	static std::vector<std::string> LoadCfgFile(const std::string& filePath);
	static SDL_Surface* LoadImageFile(const std::string& filePath);
	static void SaveGameObjectsToStr(std::string* cfgFileStr);
	static void SaveResourcesToStr(std::string* cfgFileStr);
	static void SaveComponentsToStr(std::string* cfgFileStr);
	static void SaveAllToDataCfg();
	static void LoadObjFile(ObjModel* objModel, const std::string& filePath);
};