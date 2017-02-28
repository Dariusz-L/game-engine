#pragma once

#include "..\..\..\Config\Include\IncludeGLM.h"

#include "..\..\..\Resource\Component\Component.h"

#include <vector>
#include <string>

class Shader;
class Texture;

class Material :
	public Component
{
private:
	Shader* _shader;

	std::string _name;

	glm::vec3 _colorAmbient;
	glm::vec3 _colorDiffuse;
	glm::vec3 _colorSpecular;

	Texture* _texDiffuse;
	float _shininessSpecular;
	Texture* _texSpecular;
	Texture* _texBump;
	Texture* _texNormal;

public:
	Material();
	~Material();

	void Parse(ParsedData& data) override;
	ParsedData GetParsedData() override;

	std::string GetName();
	glm::vec3 GetColorAmbient();
	glm::vec3 GetColorDiffuse();
	glm::vec3 GetColorSpecular();
	Shader* GetShader();
	Texture* GetTexDiffuse();
	float GetShininessSpecular();
	Texture* GetTexSpecular();
	Texture* GetTexBump();
	Texture* GetTexNormal();
};

