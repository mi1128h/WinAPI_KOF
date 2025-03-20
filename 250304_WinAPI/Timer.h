#pragma once
#include "config.h"
class Timer
{
public:
	void Init();
	float GetElapsedTime() { return elapsedTime / 1000.0f; }
	void Tick();

private:
	__int64 lastTime;
	__int64 elapsedTime;
};

