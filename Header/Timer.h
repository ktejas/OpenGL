#pragma once
#ifndef TIMER_H
#define TIMER_H

#include "windows.h"

class Timer
{
public:
	static void Update();
	static float GetDeltaTime();

private:
	static __int64 m_prevFrame;
	static __int64 m_currentFrame;
	static __int64 m_freq; //Frequency
	static float m_deltaTime;
};

#endif