// SystemUtils.h

#ifndef SYSTEMUTILS_H_INCLUDED
#define SYSTEMUTILS_H_INCLUDED

class OSSystem
{
public:
	OSSystem();
	~OSSystem();

	void Update();
	void Init();
	void Exit();
};

class Timer
{
	friend class OSSystem;
public:
	static void Init();
	static void Exit();

	static u64 HighResDeltaUs();
	static f64 HighResDeltaS();
	static u32 LowResDeltaMs();
	static f32 LowResDeltaS();
	static u32 GetTotalAppTime();

private:
	static void update();

private:
	static bool msIsInit;
	static f64 msCpuFreq;
	static LARGE_INTEGER msHighResCurr,msHighResPrev;
	static LARGE_INTEGER msHighTimerStart;
	static u32 msLowResCurr,msLowResPrev;
	static u32 msLowTimerStart;
	static f64 msDeltaTimed;
	static f32 msDeltaTimef;
};

#endif // SYSTEMUTILS_H_INCLUDED
