#include "Material.h"
#include "..\..\..\..\Resources\ResourceManager.h"
#include "..\..\..\..\Engine.h"

Material::Material()
{
	_shader = nullptr;

	_texDiffuse = nullptr;
	_shininessSpecular = 1;
	_texSpecular = nullptr;
	_texBump = nullptr;
}

Material::~Material()
{
}

void Material::Parse(ParsedData& data)
{
	ResourceManager* rm = Engine::GetManager<ResourceManager>();

	using namespace std;

	_name = ParseUtil::GetParseDataElementByKey("name", data);

	_isFromFile = stoi(ParseUtil::GetParseDataElementByKey("isFromFile", data)) == 0 ? false : true;

	_colorAmbient = ParseUtil::FromStringToVec3(ParseUtil::GetParseDataElementByKey("colorAmbient", data));
	_colorDiffuse = ParseUtil::FromStringToVec3(ParseUtil::GetParseDataElementByKey("colorDiffuse", data));
	_colorSpecular = ParseUtil::FromStringToVec3(ParseUtil::GetParseDataElementByKey("colorSpecular", data));

	int shaderID = stoi(ParseUtil::GetParseDataElementByKey("shader", data));
	_shader = rm->GetResourceByID<Shader>(shaderID);

	int texDiffuseID = stoi(ParseUtil::GetParseDataElementByKey("texDiffuse", data));
	_texDiffuse = rm->GetResourceByID<Texture>(texDiffuseID);

	float shininessSpecular = stof(ParseUtil::GetParseDataElementByKey("shininessSpecular", data));
	_shininessSpecular = 0 < shininessSpecular < 1 ? shininessSpecular : 1;

	int texSpecularID = stoi(ParseUtil::GetParseDataElementByKey("texSpecular", data));
	_texSpecular = rm->GetResourceByID<Texture>(texSpecularID);
	
	int texBumpID = stoi(ParseUtil::GetParseDataElementByKey("texBump", data));
	_texBump = rm->GetResourceByID<Texture>(texBumpID);

	int texNormalID = stoi(ParseUtil::GetParseDataElementByKey("texNormal", data));
	_texNormal = rm->GetResourceByID<Texture>(texNormalID);
}

ParsedData Material::GetParsedData()
{
	ParsedData data = Component::GetParsedData();

	data["name"] = _name;

	data["colorAmbient"]		= ParseUtil::FromVec3ToString(_colorAmbient);
	data["colorDiffuse"]		= ParseUtil::FromVec3ToString(_colorDiffuse);
	data["colorSpecular"]		= ParseUtil::FromVec3ToString(_colorSpecular);
	data["shininessSpecular"]	= std::to_string(_shininessSpecular);

	data["texDiffuse"]			= ParseUtil::GetObjectID(_texDiffuse);
	data["texSpecular"]			= ParseUtil::GetObjectID(_texSpecular);
	data["texBump"]				= ParseUtil::GetObjectID(_texBump);
	data["texNormal"]			= ParseUtil::GetObjectID(_texNormal);

	data["shader"]				= ParseUtil::GetObjectID(_shader);

	return data;
}

Shader* Material::GetShader()
{
	return _shader;
}

Texture* Material::GetTexDiffuse()
{
	return _texDiffuse;
}

float Material::GetShininessSpecular()
{
	return _shininessSpecular;
}

Texture* Material::GetTexSpecular()
{
	return _texSpecular;
}

Texture* Material::GetTexBump()
{
	return _texBump;
}

Texture* Material::GetTexNormal()
{
	return _texNormal;
}

std::string Material::GetName()
{
	return _name;
}

glm::vec3 Material::GetColorAmbient()
{
	return _colorAmbient;
}

glm::vec3 Material::GetColorDiffuse()
{
	return _colorDiffuse;
}

glm::vec3 Material::GetColorSpecular()
{
	return _colorSpecular;
}
