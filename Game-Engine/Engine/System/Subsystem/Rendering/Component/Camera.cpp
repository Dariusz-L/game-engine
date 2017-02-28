#include "Camera.h"
#include "..\..\..\..\Resources\ResourceManager.h"
#include "..\..\..\..\Engine.h"

#include <stdexcept>

Camera::Camera() :
	_gameObject			(nullptr),
	_lookObjectTarget	(nullptr),
	_projectionMatrix()
{
	_projectionMode = ProjectionMode::PERSPECTIVE;
	SetZoom(45.0f);
}

Camera::~Camera() {
}

void Camera::Parse(ParsedData& data) {
	ResourceManager* resourceManager = Engine::GetManager<ResourceManager>();

	GameObject* tmp;

	try {
		std::string id = data.at("gameObject");
		_gameObject = resourceManager->GetGameObjectByID(::stoi(id));
	} catch (std::out_of_range e) {

	}

	try {
		std::string id = data.at("lookObjectTarget");
		_lookObjectTarget = resourceManager->GetGameObjectByID(::stoi(id));
	} catch (std::out_of_range e) {

	}

	UpdateViewMatrix();
}

ParsedData Camera::GetParsedData() {
	ParsedData data = Component::GetParsedData();

	data["gameObject"] = std::to_string(_gameObject ? _gameObject->GetID() : -1);
	data["lookObjectTarget"] = std::to_string(_lookObjectTarget ? _lookObjectTarget->GetID() : -1);

	return data;
}

GameObject* Camera::GetLookObjectTarget() {
	return _lookObjectTarget;
}

void Camera::SetLookObjectTarget(GameObject* lookObjectTarget) {
	_lookObjectTarget = lookObjectTarget;
}

void Camera::UpdateViewMatrix() {
	if (_lookObjectTarget != nullptr)
		_viewMatrix = glm::lookAt(_gameObject->GetPos(), _lookObjectTarget->GetPos(), _gameObject->GetUpNormal());
	else
		_viewMatrix = glm::lookAt(_gameObject->GetPos(), _gameObject->GetPos() + _gameObject->GetFrontNormal(), _gameObject->GetUpNormal());
}

glm::mat4 Camera::GetViewMatrix() {
	_viewMatrix = glm::lookAt(_gameObject->GetPos(), _gameObject->GetPos() + _gameObject->GetFrontNormal(), _gameObject->GetUpNormal());
	return _viewMatrix;
}

void Camera::SetGameObject(GameObject* gameObject) {
	_gameObject = gameObject;
}

glm::mat4& Camera::GetProjectionMatrix() {
	return _projectionMatrix;
}

ProjectionMode Camera::GetProjectionMode() {
	return _projectionMode;
}

void Camera::SetProjectionMode(ProjectionMode projectionMode) {
	glm::ivec2 size = Engine::data.rendering.window.GetSize();

	if (projectionMode == ProjectionMode::ORTHOGRAPHIC)
		;// ORTHOGRAPHIC;
	else if (projectionMode == ProjectionMode::PERSPECTIVE)
		_projectionMatrix = glm::perspective(_zoom, (float) size.x / (float) size.y, 0.1f, 1000.0f);

	_projectionMode = projectionMode;
}

void Camera::SetZoom(float value) {
	_zoom = value;
	SetProjectionMode(_projectionMode);
}

float Camera::GetZoom() {
	return _zoom;
}