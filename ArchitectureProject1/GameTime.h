#pragma once

#ifndef _GAMETIME_H_
#define _GAMETIME_H_

#include <chrono>
class GameTime
{
public:
	static GameTime& Instance()
	{
		if (instance == nullptr)
		{
			instance = new GameTime();
			instance->Initialize();
		}
		return *instance;
	}

	void Destroy()
	{
		if (instance == nullptr)
		{
			delete instance;
		}
	}

	void Update();

	float DeltaTime() { return deltaTime.count(); }
	float TotalTime() { return totalTime.count(); }
	unsigned int FrameCount() { return frameCount; }

private:
	void Initialize();

private:
	unsigned int frameCount = 0;
	std::chrono::duration<float> deltaTime = std::chrono::duration<float>(0.0f);
	std::chrono::duration<float> totalTime = std::chrono::duration<float>(0.0f);
	std::chrono::time_point<std::chrono::system_clock> beginTime;
	std::chrono::time_point<std::chrono::system_clock> endTime;

	static GameTime* instance;

private:
	inline explicit GameTime() = default;
	inline ~GameTime() = default;
	inline explicit GameTime(GameTime const&) = delete;
	inline GameTime& operator=(GameTime const&) = delete;
};

#endif