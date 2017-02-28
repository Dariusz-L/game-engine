#include "TimeManager.h"
#include "..\System\Config\Include\IncludeSDL.h"

float Timer::_curFrame = 0;
float Timer::_lastFrame = 0;
float Timer::_delta = 0;

void Timer::ProcessTimer()
{
	_curFrame = SDL_GetTicks();
	_delta = _curFrame - _lastFrame;
	_lastFrame = _curFrame;
}

float Timer::GetDelta()
{
	return _delta;
}