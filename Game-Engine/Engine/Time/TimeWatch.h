#pragma once

#include <vector>
#include <chrono>

using TimePoint = std::chrono::high_resolution_clock::time_point;

class TimeWatch
{
private:
	static std::vector<TimePoint> _timePoints;

public:
	TimeWatch();
	~TimeWatch();

	static int StartNew();
	static int Stop(int handle);
};