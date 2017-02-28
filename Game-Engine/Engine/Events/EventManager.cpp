#include "EventManager.h"
#include "..\Engine.h"
#include "..\Events\IEventHandler.h"

EventManager::EventManager()
{
	_isHoldingMouseButton = false;
	_isHoldingKey = false;
	_heldButton = '\0';
}

EventManager::~EventManager()
{
}

void EventManager::Init()
{
	for (int i = 0; i < 16; i++) {
		_heldMouseButtons[i] = false;
	}

	for (int i = 0; i < 2048; i++) {
		_heldKeys[i] = false;
	}
}

void EventManager::Close()
{
}

void EventManager::Run()
{
#ifdef _SDL_H
	std::vector<SDL_Event> eventQueue;
	while (SDL_PollEvent(&ev) != 0)
		eventQueue.push_back(ev);
	bool fingerMotion = false;
	for (auto ev : eventQueue) {
		switch (ev.type) {
		case SDL_QUIT:
			Engine::Exit();
			break;

		case SDL_WINDOWEVENT:
			OnWindowEvent(ev);
			break;

		case SDL_KEYDOWN:
			OnKeyDownEvent(ev);
			break;
		case SDL_KEYUP:
			OnKeyUpEvent(ev);
			break;

		case SDL_MOUSEBUTTONDOWN:
			OnMouseButtonDownEvent(ev);
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonUpEvent(ev);
			break;
		case SDL_MOUSEMOTION:
			OnMouseMotionEvent(ev);
			break;
		case SDL_MOUSEWHEEL:
			OnMouseWheelEvent(ev);
			break;

		case SDL_FINGERDOWN:
			OnFingerDownEvent(ev);
			break;
		case SDL_FINGERUP:
			OnFingerUpEvent(ev);
			break;
		case SDL_FINGERMOTION:
			fingerMotion = true;
			OnFingerMotionEvent(ev);
			break;
		}
	}

#endif
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (_isHoldingMouseButton) {
		for (auto handler : _eventHandlers)
			handler->OnPointerHold(x, y, _heldButton);
	}

	if (_isHoldingKey)
		for (auto handler : _eventHandlers)
			handler->OnKeysHold(_heldKeys);

#ifndef __ANDROID__ 
	for (int i = 0; i < 16; i++) {
		if (_heldMouseButtons[i]) {
			OnMousePointerMotionEvent(ev);
			break;
		}
	}
#endif
}

void EventManager::AddHandler(IEventHandler* handler)
{
	_eventHandlers.push_back(handler);
}

void EventManager::RemoveHandler(IEventHandler* handler)
{
	int foundInd = -1;
	for (int i = 0; i < _eventHandlers.size(); i++)
		if (_eventHandlers[i] == handler) {
			foundInd = i;
			break;
		}

	if (foundInd != -1)
		_eventHandlers.erase(_eventHandlers.begin() + foundInd);
}

int EventManager::GetEventHandlersCount()
{
	return _eventHandlers.size();
}

void EventManager::OnWindowEvent(SDL_Event& ev)
{
	if (ev.window.event == SDL_WINDOWEVENT_RESIZED) {
		for (auto handler : _eventHandlers) {
			handler->OnResizeWindow();
		}
	}
}

void EventManager::OnKeyDownEvent(SDL_Event& ev)
{
	if (ev.key.repeat != 0)
		return;

	int sym = ev.key.keysym.sym;
	int scancode = ev.key.keysym.scancode;

	_heldKeys[scancode] = true;
	_isHoldingKey = true;
	SDL_Log("KeyDownEvent");
	for (auto handler : _eventHandlers) {
		handler->OnKeysDown(_heldKeys);
		SDL_Log("KeyDownEvent handler");
	}
}

void EventManager::OnKeyUpEvent(SDL_Event& ev)
{
	int sym = ev.key.keysym.sym;
	int scancode = ev.key.keysym.scancode; 

	_heldKeys[scancode] = false;
	_isHoldingKey = false;

	for (auto handler : _eventHandlers)
		handler->OnKeysUp(_heldKeys);
}

void EventManager::OnMouseButtonDownEvent(SDL_Event& ev)
{
	_isHoldingMouseButton = true;
	_heldButton = ev.button.button;
	_heldMouseButtons[ev.button.button] = true;
	
	int x, y;
	SDL_GetMouseState(&x, &y);
	for (auto handler : _eventHandlers)
		handler->OnPointerDown(x, y, _heldButton);
}

void EventManager::OnMouseButtonUpEvent(SDL_Event& ev)
{
	_isHoldingMouseButton = false;
	_heldMouseButtons[ev.button.button] = false;

	int x, y;
	SDL_GetMouseState(&x, &y);
	for (auto handler : _eventHandlers)
		handler->OnPointerUp(x, y, ev.button.button);
}

void EventManager::OnMouseMotionEvent(SDL_Event& ev)
{
	int x, y;
	float dX, dY;

	SDL_GetMouseState(&x, &y);
	dX = ev.motion.xrel, dY = ev.motion.yrel;

	_mouseMotion.x = dX / 1000.0f;
	_mouseMotion.y = dY / 1000.0f;

	for (auto handler : _eventHandlers)
		handler->OnMouseMotion(x, y, dX / 1000.0f, dY / 1000.0f, ev.button.button);
}

void EventManager::OnMouseWheelEvent(SDL_Event& ev)
{
	for (auto handler : _eventHandlers)
		handler->OnMouseScroll(ev.wheel.x, ev.wheel.y, ev.wheel.windowID);
}

void EventManager::OnFingerDownEvent(SDL_Event& ev)
{
	_heldButton = ev.button.button;

	int x = ev.tfinger.x;
	int y = ev.tfinger.y;
	for (auto handler : _eventHandlers)
		handler->OnPointerDown(x, y, _heldButton);
}

void EventManager::OnFingerUpEvent(SDL_Event& ev)
{
	int x = ev.tfinger.x;
	int y = ev.tfinger.y;
	for (auto handler : _eventHandlers)
		handler->OnPointerUp(x, y, ev.button.button);
}

void EventManager::OnFingerMotionEvent(SDL_Event& ev)
{
	int x, y;
	float dX = 0, dY = 0;
	
	x = ev.tfinger.x, y = ev.tfinger.y;
	dX = ev.tfinger.dx, dY = ev.tfinger.dy;

	_heldMouseButtons[SDL_BUTTON_LEFT] = true;
	for (auto handler : _eventHandlers)
		handler->OnPointerMotion(x, y, dX, dY, _heldMouseButtons);
	_heldMouseButtons[SDL_BUTTON_LEFT] = false;
	
}

void EventManager::OnMousePointerMotionEvent(SDL_Event& ev)
{
	int x, y;
	float dX = 0, dY = 0;

	SDL_GetMouseState(&x, &y);
	dX = ev.motion.xrel, dY = ev.motion.yrel;

	for (auto handler : _eventHandlers)
		handler->OnPointerMotion(x, y, _mouseMotion.x, _mouseMotion.y, _heldMouseButtons);

	_mouseMotion.x = 0;
	_mouseMotion.y = 0;
}