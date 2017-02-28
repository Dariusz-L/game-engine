#pragma once

class Timer
{
private:
	static float _curFrame;
	static float _lastFrame;
	static float _delta;

public:
	static void ProcessTimer();
	static float GetDelta();
};