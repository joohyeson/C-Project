#include <chrono>
#include "GameStateManager.h"
#include "Engine.h"

#define LIMITETIME 5

Engine::Engine() : gameStateManager() {};

Engine::~Engine() 
{
}

void Engine::Init(std::string windowName)
{
    window.Init(windowName);
}

void Engine::Shutdown()
{
    gameStateManager.Shutdown();
}

void  Engine::Update()
{
    now = std::chrono::system_clock::now();
    double dt = std::chrono::duration<double>(now - lastTick).count();

    if (dt >= (1 / Engine::Target_FPS))
    {
        lastTick = now;
        timer += dt;
        ++frameCount;

        window.Update();
        gameStateManager.Update(dt);
    }

    double aveFrameRate = frameCount / timer;

    if (timer >= LIMITETIME)
    {
        timer = 0;
        frameCount = 0;
    }
}

bool  Engine::HasGameEnded()
{
    return gameStateManager.HasGameEnded();
}
