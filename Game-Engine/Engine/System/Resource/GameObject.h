#pragma once

#include "..\Config\Include\IncludeGLM.h"

#include "..\..\Utils\ParseUtil.h"
#include "Object.h"
#include "Component\Component.h"
#include <vector>
#include <string>

class Shader;
class Mesh;
class Model;
class Camera;

class GameObject : public Object
{
private:
	std::string _name;
	std::vector<Component*> _components;

	GameObject* _parent;
	std::vector<GameObject*> _subObjects;
	
	Model* _model;
	Camera* _camera;

	glm::mat4 _modelMatrix;
	glm::mat3 _inversedModelMatrix;

	glm::vec3 _pos;
	glm::vec3 _rot;
	glm::vec3 _scale;

public:
	glm::vec3& GetPos();
	glm::vec3& GetRot();
	glm::vec3& GetScale();

	void SetPos(glm::vec3& value);
	void SetRot(glm::vec3& value);
	void SetScale(glm::vec3& value);

	void AddPos(glm::vec3& value);
	void AddRot(glm::vec3& value);
	void AddScale(glm::vec3& value);

	glm::mat4& GetModel();
	glm::mat3& GetInversedModel();

	bool changedTransform = true;
	bool setMaterial = true;

	glm::vec3 GetFrontNormal();
	glm::vec3 GetRightNormal();
	glm::vec3 GetUpNormal();

	GameObject();
	~GameObject();

	glm::mat4 GetModelMatrix();
	std::string GetName();
	void SetName(const std::string& name);
	void Parse(ParsedData& data);

	GameObject* GetParent();
	std::vector<GameObject*>* GetSubObjects();

	std::vector<Component*> GetComponents();
	void AddComponent(Component* component);
	template<class T>
	T* GetComponentOfType() {
		for (auto c : _components) 
			if (typeid(*c) == typeid(T))
				return static_cast<T*>(c);

		return nullptr;
	}
};

