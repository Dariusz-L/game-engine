#pragma once
#include "..\..\..\Resource\Asset\Asset.h"
#include "..\..\..\Resource\Asset\Parser\OBJ\TinyObj\TinyObjLoaderStructs.h"

#include <map>
#include <unordered_map>
#include <vector>

class Material;

class MtlMaterial :
	public Asset
{
private:
	std::map<std::string, int> _materialMap;
	std::unordered_map<int, Material*> _materials;
	std::vector<TinyObj::material_t> _tMaterials;

public:
	MtlMaterial();
	~MtlMaterial();

	void Load(std::vector<std::string>& filePaths) override;

	std::map<std::string, int> GetMaterialMap();
	std::vector<TinyObj::material_t> GetTMaterials();

	Material* GetMaterial(const std::string& name);
	std::unordered_map<int, Material*>* GetMaterials();
};