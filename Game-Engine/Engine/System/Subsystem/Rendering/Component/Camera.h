#pragma once

#include "..\..\..\Config\Include\IncludeGLM.h"

#include "..\..\..\Resource\Component\Component.h"

enum class ProjectionMode : unsigned char {
	PERSPECTIVE,
	ORTHOGRAPHIC
};

class GameObject;

class Camera :
	public Component
{
private:
	GameObject* _gameObject;
	GameObject* _lookObjectTarget;

	glm::mat4 _viewMatrix;
	glm::mat4 _projectionMatrix;
	ProjectionMode _projectionMode;
	float _zoom;

public:
	Camera();
	~Camera();

	void UpdateViewMatrix();
	glm::mat4 GetViewMatrix();

	void Parse(ParsedData& data) override;
	ParsedData GetParsedData() override;

	GameObject* GetLookObjectTarget();
	void SetLookObjectTarget(GameObject* lookObjectTarget);

	void SetGameObject(GameObject* gameObject);
	
	glm::mat4& GetProjectionMatrix();

	ProjectionMode GetProjectionMode();
	void SetProjectionMode(ProjectionMode projectionMode);

	void SetZoom(float value);
	float GetZoom();
};

