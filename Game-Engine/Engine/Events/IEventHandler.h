#pragma once

class IEventHandler
{
public:
	virtual	~IEventHandler() {};

	virtual void OnPointerUp(int x, int y, char pointerCode) {}
	virtual void OnPointerHold(int x, int y, char pointerCode) {}
	virtual void OnPointerDown(int x, int y, char pointerCode) {}
	virtual void OnPointerMotion(int x, int y, float dx, float dy, bool heldButtons[]) {}

	virtual void OnMouseScroll(int x, int y, int windowID) {}
	virtual void OnMouseMotion(int x, int y, float dx, float dy, char pointerCode) {}

	virtual void OnKeysDown(bool keys[]) {}
	virtual void OnKeysHold(bool keys[]) {}
	virtual void OnKeysUp(bool keys[]) {}

	virtual void OnResizeWindow() {}
};

