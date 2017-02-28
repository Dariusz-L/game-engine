#include "Window.h"

#include "..\..\Config\Platform.h"

const glm::ivec2 Window::DEFAULT_SIZE(800, 600);

Window::Window() :
	_window(nullptr) {}

glm::vec2 Window::GetSize() {

	glm::ivec2 size;
	SDL_GetWindowSize(_window, &size.x, &size.y);
	return size;
}

void Window::Create() {

#if defined(_PLATFORM_WINDOWS_) || defined(_PLATFORM_EDITOR_)
	_window = SDL_CreateWindow("Window", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		DEFAULT_SIZE.x, DEFAULT_SIZE.y, 
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

#else
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	_window = SDL_CreateWindow("Window", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		dm.w, dm.h, 
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

#endif

	_glContext = SDL_GL_CreateContext(_window);
	SDL_GL_MakeCurrent(_window, _glContext);
}

void Window::Destroy() {
	SDL_DestroyWindow(_window);
}

SDL_Window* Window::GetWindow() const {
	return _window;
}