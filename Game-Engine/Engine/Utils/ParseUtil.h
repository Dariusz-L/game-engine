#pragma once

#include "..\System\Config\Include\IncludeGLM.h"

#include <unordered_map>
#include <string>

class Object;
class Component;

using ParsedData = std::unordered_map<std::string, std::string>;

class ParseUtil
{
public:
	static ParsedData ParseLoadedData(const std::string& data);
	static Component* GetRightComponentByStrAndID(const std::string& str, int id);
	static std::string GetParseDataElementByKey(const std::string& key, ParsedData& parsedData);
	static std::string GetTextureIDByName(const std::string& materialName);
	static std::vector<std::pair<std::string, std::string>> GetOrderedResourcesNames();
	static glm::vec3 FromStringToVec3(const std::string& data);
	static std::string FromVec3ToString(const glm::vec3 &vec3);
	static std::string GetObjectID(Object* object);
	static std::vector<std::string> GetMaterialsFromStr(const std::string& str);
};