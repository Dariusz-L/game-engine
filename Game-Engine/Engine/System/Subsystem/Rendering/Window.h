#pragma once

#include "..\..\Config\Include\IncludeGLM.h"
#include "..\..\Config\Include\IncludeSDL.h"

#include <string>

class Window
{
private:
	SDL_GLContext	_glContext;
	SDL_DisplayMode _displayMode;
	SDL_Window*		_window;

	static const glm::ivec2 DEFAULT_SIZE;

public:
	Window();

	void Create();
	void Destroy();

	glm::vec2 GetSize();

	SDL_Window* GetWindow() const;
};