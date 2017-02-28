#pragma once
#include "..\..\..\Resource\Component\Component.h"
#include "..\..\..\Config\Include\IncludeGLM.h"

class Shader;
class Model;

enum class LightType
{
	DIRECTIONAL,
	POINT,
	SPOT
};

class Light :
	public Component
{
private:
	Shader* _shader;
	Model* _optionalLightModel;

	LightType _type;

public:
	Light();
	~Light();

	void Parse(ParsedData& data) override;
	ParsedData GetParsedData() override;
	
	glm::vec3 color;

	Shader* GetShader();
	void SetShader(Shader* shader);

	Model* GetModel();
	void SetModel(Model* model);

	LightType GetType();
};

