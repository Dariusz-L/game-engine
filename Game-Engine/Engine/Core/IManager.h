#pragma once

class IManager
{
public:
	virtual ~IManager() {}

	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void Close() = 0;
};