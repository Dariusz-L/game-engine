#include "GameObject.h"
#include "Component\Component.h"
#include "..\..\Resources\ResourceManager.h"
#include "..\Subsystem\Rendering\Component\Camera.h"
#include "..\..\Engine.h"
#include "..\..\Utils\ParseUtil.h"

#include "..\Config\Include\IncludeGLM.h"
#include <stdexcept>
#include <functional>

using namespace std;

GameObject::GameObject() :
	_modelMatrix()
{
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;

	SetPos(pos = glm::vec3(0.0f, 0.0f, 0.0f));
	SetRot(rot = glm::vec3(0.0f, 0.0f, 0.0f));
	SetScale(scale = glm::vec3(1.0f, 1.0f, 1.0f));

	_model = nullptr;
	_parent = nullptr;
	_camera = nullptr;
}

GameObject::~GameObject()
{
}

glm::mat4& GameObject::GetModel()
{
	return _modelMatrix;
}

glm::mat3& GameObject::GetInversedModel()
{
	return _inversedModelMatrix;
}

void GameObject::AddPos(glm::vec3& value)
{
	_pos += value;

	_modelMatrix = glm::translate(_modelMatrix, value);
	_inversedModelMatrix = glm::mat3(glm::inverse(_modelMatrix));
}

void GameObject::AddRot(glm::vec3& value)
{
	_rot += value;

	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rot.x), glm::vec3(1.0, 0.0f, 0.0f));
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rot.y), glm::vec3(0.0, 1.0f, 0.0f));
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rot.z), glm::vec3(0.0, 0.0f, 1.0f));
	_inversedModelMatrix = glm::mat3(glm::inverse(_modelMatrix));
}

void GameObject::AddScale(glm::vec3& value)
{
	_scale += value;
	_modelMatrix = glm::scale(_modelMatrix, _scale);
	_inversedModelMatrix = glm::mat3(glm::inverse(_modelMatrix));
}

void GameObject::SetPos(glm::vec3& value)
{
	_pos = value;
	_modelMatrix = glm::translate(_modelMatrix, value);
	_inversedModelMatrix = glm::mat3(glm::inverse(_modelMatrix));
}

void GameObject::SetRot(glm::vec3& value)
{
	_rot = value;

	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rot.x), glm::vec3(1.0, 0.0f, 0.0f));
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rot.y), glm::vec3(0.0, 1.0f, 0.0f));
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rot.z), glm::vec3(0.0, 0.0f, 1.0f));
	_inversedModelMatrix = glm::mat3(glm::inverse(_modelMatrix));
}

void GameObject::SetScale(glm::vec3& value)
{
	_scale = value;

	_modelMatrix = glm::scale(_modelMatrix, _scale);
	_inversedModelMatrix = glm::mat3(glm::inverse(_modelMatrix));
}

void GameObject::AddComponent(Component* component)
{
	_components.push_back(component);
}

glm::mat4 GameObject::GetModelMatrix()
{
	glm::mat4 model;

	model = glm::translate(model, _pos);
	model = glm::rotate(model, glm::radians(_rot.x), glm::vec3(1.0, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(_rot.y), glm::vec3(0.0, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(_rot.z), glm::vec3(0.0, 0.0f, 1.0f));
	model = glm::scale(model, _scale);

	return model;
}

std::string GameObject::GetName()
{
	return _name;
}

void GameObject::SetName(const std::string& name)
{
	_name = name;
}

void GameObject::Parse(ParsedData& data)
{
	ResourceManager* resourceManager = Engine::GetManager<ResourceManager>();

	glm::vec3 pos = ParseUtil::FromStringToVec3(ParseUtil::GetParseDataElementByKey("pos", data));
	glm::vec3 rot = ParseUtil::FromStringToVec3(ParseUtil::GetParseDataElementByKey("rot", data));
	glm::vec3 scale = ParseUtil::FromStringToVec3(ParseUtil::GetParseDataElementByKey("scale", data));

	SetPos(pos);
	SetRot(rot);
	SetScale(scale);

	std::function<void (const std::string&)> TryAddComponent = 
		[this, resourceManager, &data] 
		(const std::string& key) -> void {
		try {
			int componentID = ::atoi(data.at(key).c_str());
			Component* c = ParseUtil::GetRightComponentByStrAndID(key, componentID);
			if (c)
				_components.push_back(c);
		} catch (const std::out_of_range& e) {
		}
	};
	
	TryAddComponent("model");
	TryAddComponent("camera");
	TryAddComponent("light");

	if (GetComponentOfType<Camera>() != nullptr) {
		Engine::data.rendering.mainCamera = this;
		GetComponentOfType<Camera>()->SetGameObject(this);
	}

	if (GetComponentOfType<Light>() != nullptr) {
		Engine::data.rendering.lights.push_back(this);
	}
}

glm::vec3 GameObject::GetFrontNormal()
{
	glm::vec3 front;

	front.x = cos(glm::radians(_rot.y)) * cos(glm::radians(_rot.x));
	front.y = sin(glm::radians(_rot.x));
	front.z = sin(glm::radians(_rot.y)) * cos(glm::radians(_rot.x));
	
	return glm::normalize(front);
}

glm::vec3 GameObject::GetRightNormal()
{
	return glm::normalize(glm::cross(GetFrontNormal(), glm::vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 GameObject::GetUpNormal()
{
	return glm::normalize(glm::cross(GetRightNormal(), GetFrontNormal()));
}

GameObject* GameObject::GetParent()
{
	return _parent;
}

std::vector<GameObject*>* GameObject::GetSubObjects()
{
	return &_subObjects;
}

std::vector<Component*> GameObject::GetComponents()
{
	return _components;
}

glm::vec3& GameObject::GetPos()
{
	return _pos;
}

glm::vec3& GameObject::GetRot()
{
	return _rot;
}

glm::vec3& GameObject::GetScale()
{
	return _scale;
}