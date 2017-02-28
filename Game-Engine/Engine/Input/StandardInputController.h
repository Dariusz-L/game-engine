#pragma once
#include "..\Events\IEventHandler.h"
#include <string>

class GameObject;

class StandardInputController :
	public IEventHandler
{
private:
	GameObject* _curObjectSelected;

public:
	StandardInputController();
	void OnMouseScroll(int x, int y, int windowID) override;

	void OnPointerUp(int x, int y, char pointerCode) override;
	void OnPointerHold(int x, int y, char pointerCode) override;
	void OnPointerDown(int x, int y, char pointerCode) override;
	void OnPointerMotion(int x, int y, float dx, float dy, bool heldButtons[]) override;

	void OnKeysDown(bool keys[]) override;
	void OnKeysHold(bool keys[]) override;

	void UpdateObjectTransform(
		float posX, float posY, float posZ,
		float rotX, float rotY, float rotZ,
		float scaleX, float scaleY, float scaleZ,
		const std::string& name);

	GameObject* GetCurObjectSelected();
	bool SelectObjectById(int id);
};

