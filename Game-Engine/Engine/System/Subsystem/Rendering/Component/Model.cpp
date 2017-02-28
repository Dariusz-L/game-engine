#include "Model.h"
#include <string>
#include "..\..\..\Utility\String\StringUtility.h"
#include "..\..\..\..\Resources\ResourceManager.h"
#include "..\..\..\..\Engine.h"

using namespace std;

Model::Model()
{
}

Model::~Model()
{
}

void Model::Parse(ParsedData& data)
{
	ResourceManager* rm = Engine::GetManager<ResourceManager>();
	
	_isFromFile = stoi(ParseUtil::GetParseDataElementByKey("isFromFile", data)) == 0 ? false : true;
	
	if (!_isFromFile) {
		auto materialsData = ParseUtil::GetMaterialsFromStr(data["materials"]);
		for (string& m : materialsData) {
			_materials.push_back(rm->GetComponentByID<Material>(::stoi(m)));
		}

		_objModel = rm->GetResourceByID<ObjModel>(::stoi(data["objModel"]));
	}
}

ParsedData Model::GetParsedData()
{
	ParsedData p = Component::GetParsedData();
	
	string materialsValues("(");
	for (int i = 0; i < _materials.size(); i++) {
		materialsValues += ::to_string(_materials[i]->GetID());
		if (i != _materials.size() - 1)
			materialsValues += ';';
	}
	materialsValues += ')';
	p["materials"] = materialsValues;
	p["objModel"] = ::to_string(_objModel->GetID());

	return p;
}

ObjModel* Model::GetObjModel()
{
	return _objModel;
}

void Model::SetObjModel(ObjModel* objModel)
{
	_objModel = objModel;
}


std::vector<Material*>* Model::GetMaterials()
{
	return &_materials;
}