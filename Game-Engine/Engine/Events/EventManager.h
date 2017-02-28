#pragma once
#include "..\Core\IManager.h"
#include "..\System\Config\Include\IncludeGLM.h"
#include "..\System\Config\Include\IncludeSDL.h"
#include <vector>

class IEventHandler;

class EventManager :
	public IManager
{
private:
	SDL_Event ev;
	std::vector<IEventHandler*> _eventHandlers;

	void OnWindowEvent(SDL_Event& ev);
	void OnKeyDownEvent(SDL_Event& ev);
	void OnKeyUpEvent(SDL_Event& ev);
	void OnMouseButtonDownEvent(SDL_Event& ev);
	void OnMouseButtonUpEvent(SDL_Event& ev);
	void OnMouseMotionEvent(SDL_Event& ev);
	void OnMousePointerMotionEvent(SDL_Event& ev);
	void OnMouseWheelEvent(SDL_Event& ev);
	void OnFingerDownEvent(SDL_Event& ev);
	void OnFingerUpEvent(SDL_Event& ev);
	void OnFingerMotionEvent(SDL_Event& ev);

	bool _isHoldingMouseButton;
	bool _isHoldingKey;
	bool _heldKeys[2048];

	char _heldButton;
	glm::vec2 _mouseMotion;
	bool _heldMouseButtons[16];

public:
	EventManager();
	~EventManager();

	void Init() override;
	void Close() override;

	void Run() override;

	void AddHandler(IEventHandler* handler);
	void RemoveHandler(IEventHandler* handler);
	int GetEventHandlersCount();
};

