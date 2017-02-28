#include "MaterialLoader.h"

#include "..\..\..\Resource\Asset\Parser\MTL\MtlAssetParsed.h"
#include "..\..\..\..\Resources\ResourceManager.h"

void MaterialLoader::Load(MtlMaterial* mtlMaterial, AssetParsed* assetParsed) {

	MtlAssetParsed* mtlAssetParsed = static_cast<MtlAssetParsed*>(assetParsed);
	mtlMaterial->_materialMap = mtlAssetParsed->map;
	ResourceManager* rm = Engine::GetManager<ResourceManager>();
	int i = 0;
	for (auto m : mtlAssetParsed->tMaterials) {
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
		mtlMaterial->GetMaterials()->emplace(mtlMaterial->GetMaterialMap()[m.name], mat);
	}
}

void MaterialLoader::Destroy(MtlMaterial* asset) {



}