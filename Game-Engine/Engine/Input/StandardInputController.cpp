#include "StandardInputController.h"
#include "..\Engine.h"
#include "..\Resources\ResourceManager.h"
#include "..\System\Subsystem\Rendering\Component\Camera.h"
#include "..\System\Resource\GameObject.h"
#include "..\Time\TimeManager.h"

StandardInputController::StandardInputController() {
	_curObjectSelected = Engine::data.rendering.mainCamera;
}

void StandardInputController::OnMouseScroll(int x, int y, int windowID)
{
	glm::vec3 pos;
	Engine::data.rendering.mainCamera->AddPos(pos = Engine::data.rendering.mainCamera->GetFrontNormal() * (float) y * 0.03f * Timer::GetDelta());
	Engine::data.rendering.mainCamera->GetComponentOfType<Camera>()->UpdateViewMatrix();
	//App::GetScreen()->zoom -= (float) y * 0.003f * Timer::GetDelta();

	//if (App::GetScreen()->zoom > 45)
	//	App::GetScreen()->zoom = 45;
	//else if (App::GetScreen()->zoom < 44)
	//	App::GetScreen()->zoom = 44;

	//SDL_Log("zoom %f", App::GetScreen()->zoom);
}

void StandardInputController::OnPointerMotion(int x, int y, float dx, float dy, bool heldButtons[])
{
	glm::vec3 tmp = glm::vec3(-dy, -dx, 0) * 60.0f;
	if (heldButtons[SDL_BUTTON_LEFT]) {
		Engine::data.rendering.mainCamera->AddRot(tmp );

		//_curObjectSelected->pos.y -= dy * 3.f;
		//_curObjectSelected->pos.x -= dx * 3.f;
	} else if (heldButtons[SDL_BUTTON_RIGHT]) {
		if (x != 0)
			Engine::data.rendering.mainCamera->AddPos(tmp = Engine::data.rendering.mainCamera->GetRightNormal() * -dx * 3.f);
		if (y != 0)
			Engine::data.rendering.mainCamera->AddPos(tmp = Engine::data.rendering.mainCamera->GetUpNormal() * dy * 3.f);
	}
	Engine::data.rendering.mainCamera->GetComponentOfType<Camera>()->UpdateViewMatrix();

}

void StandardInputController::OnKeysDown(bool keys[])
{
	if (keys[SDL_SCANCODE_P]) {
		FileLoader::SaveAllToDataCfg();
	} else if (keys[SDL_SCANCODE_O]) {
		//int shaderID = stoi(ParseUtil::GetParseDataElementID("shader", data));
		//_shader = rm->GetResourceByID<Shader>(shaderID);
	}
}

void StandardInputController::OnKeysHold(bool keys[])
{
	float speed = 0.001f;
	GameObject* cam = Engine::data.rendering.mainCamera;
	glm::vec3 tmp;
	if (keys[SDL_SCANCODE_W]) {
		cam->AddPos(tmp = cam->GetFrontNormal() * speed * Timer::GetDelta());
	} if (keys[SDL_SCANCODE_S]) {
		cam->AddPos(tmp = cam->GetFrontNormal() * -speed  * Timer::GetDelta());
	} if (keys[SDL_SCANCODE_Q]) {
		cam->AddPos(tmp = cam->GetUpNormal() * -speed  * Timer::GetDelta());
	} if (keys[SDL_SCANCODE_E]) {
		cam->AddPos(tmp = cam->GetUpNormal() * speed  * Timer::GetDelta());
	} if (keys[SDL_SCANCODE_D]) {
		cam->AddPos(tmp = cam->GetRightNormal() * speed  * Timer::GetDelta());
	} if (keys[SDL_SCANCODE_A]) {
		cam->AddPos(tmp = cam->GetRightNormal() * -speed  * Timer::GetDelta());
	}
	cam->GetComponentOfType<Camera>()->UpdateViewMatrix();
}

void StandardInputController::OnPointerUp(int x, int y, char pointerCode)
{
}

void StandardInputController::OnPointerHold(int x, int y, char pointerCode)
{
}

void StandardInputController::OnPointerDown(int x, int y, char pointerCode)
{
}

void StandardInputController::UpdateObjectTransform (
	float posX, float posY, float posZ,
	float rotX, float rotY, float rotZ,
	float scaleX, float scaleY, float scaleZ,
	const std::string& name)
{
	if (_curObjectSelected == nullptr)
		return;

	glm::vec3 tmp;
	_curObjectSelected->SetPos(tmp = glm::vec3(posX, posY, posZ));
	_curObjectSelected->SetRot(tmp = glm::vec3(rotX, rotY, rotZ));
	_curObjectSelected->SetScale(tmp = glm::vec3(scaleX, scaleY, scaleZ));

	_curObjectSelected->SetName(name);
}

GameObject* StandardInputController::GetCurObjectSelected()
{
	return _curObjectSelected;
}

bool StandardInputController::SelectObjectById(int id)
{
	GameObject* newGameObject = Engine::GetManager<ResourceManager>()->GetGameObjectByID(id);
	if (newGameObject != nullptr) {
		_curObjectSelected = newGameObject;
		return true;
	}

	return false;
}