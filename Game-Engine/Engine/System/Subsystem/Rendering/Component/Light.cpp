#include "Light.h"

#include "..\..\..\..\Resources\ResourceManager.h"
#include "..\Asset\Shader.h"

#include "Model.h"

using namespace std;

Light::Light()
{
	_shader = nullptr;
	_optionalLightModel = nullptr;
}

Light::~Light()
{
}

void Light::Parse(ParsedData& data)
{
	Component::Parse(data);

	ResourceManager* rm = Engine::GetManager<ResourceManager>();

	_type = static_cast<LightType>(::stoi(data["type"]));

	color = ParseUtil::FromStringToVec3(ParseUtil::GetParseDataElementByKey("color", data));
}

ParsedData Light::GetParsedData()
{
	ParsedData data = Component::GetParsedData();

	data["type"] = std::to_string((int) _type);
	data["color"] = ParseUtil::FromVec3ToString(color);
	
	return data;
}

Shader* Light::GetShader()
{
	return _shader;
}

void Light::SetShader(Shader* shader)
{
	_shader = shader;
}

Model* Light::GetModel()
{
	return _optionalLightModel;
}

void Light::SetModel(Model* model)
{
	_optionalLightModel = model;
}

LightType Light::GetType()
{
	return _type;
}