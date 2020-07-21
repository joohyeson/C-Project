#pragma once

#include <chrono>
#include "GameStateManager.h"
#include "Window.h"
#include <string>


class Engine {
public:
	static Engine& Instance() { static Engine instance; return instance; }
	static Window& GetWindow() { return Instance().window; }
	static GameStateManager& GetGameStateManager() { return Instance().gameStateManager; }

	void Init(std::string windowName);
	void Shutdown();
	void Update();
	bool HasGameEnded();
private:
	Engine();
	~Engine();

	GameStateManager gameStateManager;
	Window window;

	std::chrono::system_clock::time_point now, lastTick;
	static constexpr double Target_FPS = 30.0;
	double frameCount = 0;
	double timer = 0;
};