#pragma once
#include <chrono>
#include <ctime>
#include <Windows.h>



class EngineTime
{
public:
	static void create();
	static void release();

	static double getDeltaTime();
	static double getTotalTime();

private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&) {};
	EngineTime& operator=(EngineTime const&) {};

	static EngineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.f;
	double totalTime = 0.f;

	static void LogFrameStart();
	static void LogFrameEnd();

	static void ResetDeltaTime();


	LARGE_INTEGER frequency;
	LARGE_INTEGER lastTime;
	LARGE_INTEGER currentTime;

public:
	static void tick();

	friend class Window;
};