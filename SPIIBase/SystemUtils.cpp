// SystemUtils.cpp

#include "stdafx.h"
#include "SystemUtils.h"

#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")

// ossystem
OSSystem::OSSystem()
{
};

OSSystem::~OSSystem()
{
};

void OSSystem::Update()
{
	Timer::update();
};

void OSSystem::Init()
{
	Timer::Init();
};

void OSSystem::Exit()
{
	Timer::Exit();
};


// static timer
bool Timer::msIsInit=false;
f64 Timer::msCpuFreq=0.0;
LARGE_INTEGER Timer::msHighResCurr={0};
LARGE_INTEGER Timer::msHighResPrev={0};
LARGE_INTEGER Timer::msHighTimerStart={0};
u32 Timer::msLowResCurr=0;
u32 Timer::msLowResPrev=0;
f32 Timer::msDeltaTimef=0.0;
f64 Timer::msDeltaTimed=0.0;
u32 Timer::msLowTimerStart=0;

void Timer::Init()
{
	if(msIsInit) {return;};
	msIsInit=true;
	::timeBeginPeriod(1);
	LARGE_INTEGER freq;
	::QueryPerformanceFrequency(&freq);
	msCpuFreq=f64(freq.QuadPart)*0.001f;
	::QueryPerformanceCounter(&msHighTimerStart);
	msLowTimerStart=::timeGetTime();
};

void Timer::Exit()
{
	if(!msIsInit) {return;};
	msIsInit=false;
	::timeEndPeriod(1);
};

u64 Timer::HighResDeltaUs()
{
	return msHighResCurr.QuadPart-msHighResPrev.QuadPart;
};

u32 Timer::LowResDeltaMs()
{
	return msLowResCurr-msLowResPrev;
};

f32 Timer::LowResDeltaS()
{
	return msDeltaTimef;
};

f64 Timer::HighResDeltaS()
{
	return msDeltaTimed;
};

u32 Timer::GetTotalAppTime()
{
	return msLowResCurr-msLowTimerStart;
};


// update
void Timer::update()
{
	msLowResPrev=msLowResCurr;
	msLowResCurr=::timeGetTime();
	msDeltaTimef=f32(msLowResCurr-msLowResPrev)*0.001f;

	msHighResPrev=msHighResCurr;
	::QueryPerformanceCounter(&msHighResCurr);
	msDeltaTimed=f64(msHighResCurr.QuadPart-msHighResPrev.QuadPart)/f64(msCpuFreq);
};
