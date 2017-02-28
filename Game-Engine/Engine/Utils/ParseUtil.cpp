#include "ParseUtil.h"
#include "..\System\Utility\String\StringUtility.h"

#include "..\Engine.h"
#include "..\Resources\ResourceManager.h"

#include "..\System\Resource\Component\Component.h"
#include "..\System\Subsystem\Rendering\Component\Model.h"
#include "..\System\Subsystem\Rendering\Component\Light.h"
#include "..\System\Subsystem\Rendering\Component\Camera.h"
#include "..\System\Subsystem\Rendering\Component\Material.h"

#include <vector>
#include <stdexcept>

using namespace std;
using namespace Utility::String;

std::unordered_map<std::string, std::string> ParseUtil::ParseLoadedData(const std::string& data)
{
	std::unordered_map<std::string, std::string> result;

	vector<string> dataVec = Split(data, ',');
	for (auto f : dataVec) {
		vector<string> splitted = Split(f, ':');

		if (splitted[1] == "")
			splitted[1] = "-1";

		result.emplace(splitted[0], splitted[1]);
	}

	return result;
}

Component* ParseUtil::GetRightComponentByStrAndID(const std::string& str, int id)
{
	ResourceManager* rm = Engine::GetManager<ResourceManager>();

	if (str == "model")
		return rm->GetComponentByID<Model>(id);
	if (str == "camera")
		return rm->GetComponentByID<Camera>(id);
	if (str == "light")
		return rm->GetComponentByID<Light>(id);
	if (str == "material")
		return rm->GetComponentByID<Material>(id);

	return nullptr;
}

std::string ParseUtil::GetParseDataElementByKey(const std::string& key, ParsedData& parsedData)
{
	try {
		string value = parsedData.at(key);
		return value == "" ? "-1" : value;
	}
	catch (std::out_of_range e) {
		return "-1";
	}
}

std::string ParseUtil::GetTextureIDByName(const std::string& textureName)
{
	if (textureName == "")
		return "-1";

	ResourceManager* rm = Engine::GetManager<ResourceManager>();

	std::string name = Split(textureName, '.')[0];
	Texture* texture = rm->GetResourceByName<Texture>(name);

	return texture ? to_string(texture->GetID()) : "-1";
}

vector<pair<string, string>> ParseUtil::GetOrderedResourcesNames()
{
	return vector<pair<string, string>> {
		{"RTextures",		"textures.cfg"	},
		{"RShaders",		"shaders.cfg"	},
		{"RMtlMaterials",	"materials.cfg"	},
		{"RObjModels",		"objModels.cfg"	}
	};
}

glm::vec3 ParseUtil::FromStringToVec3(const std::string& data)
{
	string dataProcessed("");
	
	dataProcessed = RemoveSubstring(data, "(");
	dataProcessed = RemoveSubstring(dataProcessed, ")");

	vector<string> splittedData = Split(dataProcessed, ';');

	return glm::vec3(stof(splittedData[0]), stof(splittedData[1]), stof(splittedData[2]));
}

std::string ParseUtil::FromVec3ToString(const glm::vec3 &vec3)
{
	return "(" + to_string(vec3.x) + ";" + to_string(vec3.y) + ";" + to_string(vec3.z) + ")";
}

std::string ParseUtil::GetObjectID(Object* object)
{
	return to_string(object ? object->GetID() : -1);
}

std::vector<std::string> ParseUtil::GetMaterialsFromStr(const std::string& str)
{
	std::vector<int> result;

	string data = Utility::String::RemoveSubstring(str, "(");
	data = Utility::String::RemoveSubstring(data, ")");

	return Utility::String::Split(data, ';');
}