#include "MtlMaterial.h"
#include "..\..\..\Resource\Asset\Parser\OBJ\TinyObj\TinyObjParser.h"
#include "..\..\..\..\Loader\FileLoader.h"

#include "..\..\..\..\Utils\ParseUtil.h"
#include "..\..\..\..\Resources\ResourceManager.h"
#include "..\..\..\..\Engine.h"

#include <stdexcept>

MtlMaterial::MtlMaterial() {}
MtlMaterial::~MtlMaterial() {}

void MtlMaterial::Load(std::vector<std::string>& filePaths)
{
	Asset::Load(filePaths);

	ResourceManager* rm = Engine::GetManager<ResourceManager>();

	using namespace TinyObj;
	using namespace std;

	stringstream inStream;
	inStream << FileLoader::LoadFile(filePaths[0]);
	LoadMtl(&_materialMap, &_tMaterials, &inStream);

	int i = 0;
	for (auto m : _tMaterials) {
		ParsedData data;
		data["name"] = m.name;
		data["isFromFile"] = "1";

		data["colorAmbient"] = ParseUtil::FromVec3ToString(glm::vec3(m.ambient[0], m.ambient[1], m.ambient[2]));
		data["colorDiffuse"] = ParseUtil::FromVec3ToString(glm::vec3(m.diffuse[0], m.diffuse[1], m.diffuse[2]));
		data["colorSpecular"] = ParseUtil::FromVec3ToString(glm::vec3(m.specular[0], m.specular[1], m.specular[2]));

		data["texDiffuse"]	= ParseUtil::GetTextureIDByName(m.diffuse_texname);
		data["texSpecular"] = ParseUtil::GetTextureIDByName(m.specular_texname);
		data["texBump"]		= ParseUtil::GetTextureIDByName(m.bump_texname);
		data["texNormal"]	= ParseUtil::GetTextureIDByName(m.bump_texname);

		if (m.bump_texname != "" && m.diffuse_texname != "")
			data["shader"] = to_string(rm->GetResourceByName<Shader>("dsn")->GetID());
		else if (m.specular_texname != "" && m.diffuse_texname != "")
			data["shader"] = to_string(rm->GetResourceByName<Shader>("s")->GetID());
		else if (m.diffuse_texname != "")
			data["shader"] = to_string(rm->GetResourceByName<Shader>("d")->GetID());
		else
			data["shader"] = to_string(rm->GetResourceByName<Shader>("ac")->GetID());

		Material* mat = rm->InitComponent<Material>(data);
		_materials.emplace(_materialMap[m.name], mat);
	}
}

Material* MtlMaterial::GetMaterial(const std::string& name)
{
	try {
		return _materials.at(_materialMap.at(name));
	} catch (std::out_of_range) {
		return nullptr;
	}
}

std::map<std::string, int> MtlMaterial::GetMaterialMap()
{
	return _materialMap;
}

std::vector<TinyObj::material_t> MtlMaterial::GetTMaterials()
{
	return _tMaterials;
}

std::unordered_map<int, Material*>*  MtlMaterial::GetMaterials()
{
	return &_materials;
}