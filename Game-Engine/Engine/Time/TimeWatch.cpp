#include "TimeWatch.h"

using namespace std::chrono;

std::vector<TimePoint> TimeWatch::_timePoints;

int TimeWatch::StartNew()
{
	_timePoints.push_back(TimePoint());

	int handle = _timePoints.size() - 1;
	_timePoints[handle] = high_resolution_clock::now();

	return _timePoints.size() - 1;
}

int TimeWatch::Stop(int handle)
{
	int timeOffset = 
		duration_cast<microseconds>(high_resolution_clock::now() - _timePoints[handle]).count();

	_timePoints.erase(_timePoints.begin() + handle);

	return timeOffset;
}