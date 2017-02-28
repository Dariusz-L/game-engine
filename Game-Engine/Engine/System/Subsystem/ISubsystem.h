#pragma once

struct ISubsystem {
	virtual void OnStart()	= 0;
	virtual void Update()	= 0;
	virtual void OnEnd()	= 0;
};