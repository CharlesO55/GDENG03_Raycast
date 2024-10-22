#include "EngineTime.h"

#include "Debugger.h"


EngineTime* EngineTime::sharedInstance = NULL;

void EngineTime::create()
{
	if (sharedInstance != nullptr)
		Debugger::Error("[DUPLICATE ERROR] Engine Time");

	sharedInstance = new EngineTime();

	QueryPerformanceFrequency(&sharedInstance->frequency);
	QueryPerformanceCounter(&sharedInstance->lastTime);
	
	Debugger::Success("[Engine Time] Created");
}

void EngineTime::release()
{
	delete EngineTime::sharedInstance;
}

double EngineTime::getDeltaTime()
{
	return sharedInstance->deltaTime;
}

double EngineTime::getTotalTime()
{
	return sharedInstance->totalTime;
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
	Debugger::Warning("[Engine Time] Destroyed");
}

void EngineTime::LogFrameStart()
{
	//sharedInstance->start = std::chrono::system_clock::now();
	QueryPerformanceCounter(&sharedInstance->lastTime);
}

void EngineTime::LogFrameEnd()
{
	/*sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elpased_seconds = sharedInstance->end - sharedInstance->start;

	sharedInstance->deltaTime = elpased_seconds.count();

	sharedInstance->totalTime += sharedInstance->deltaTime;
	std::cout << sharedInstance->totalTime << std::endl;*/
}

void EngineTime::ResetDeltaTime()
{
	sharedInstance->totalTime += sharedInstance->deltaTime;
	sharedInstance->deltaTime = 0;
}

void EngineTime::tick()
{
	QueryPerformanceCounter(&sharedInstance->currentTime);
	sharedInstance->deltaTime = static_cast<double>(sharedInstance->currentTime.QuadPart - sharedInstance->lastTime.QuadPart) / sharedInstance->frequency.QuadPart;
}