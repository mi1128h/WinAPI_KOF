#include "Timer.h"

void Timer::Init()
{
	lastTime = GetTickCount64();
	elapsedTime = 0.0f;
}

void Timer::Tick()
{
	unsigned __int64 curTime = GetTickCount64();
	elapsedTime = curTime - lastTime;
	lastTime = curTime;
}
