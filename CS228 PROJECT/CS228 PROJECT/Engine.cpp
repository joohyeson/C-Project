/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Engine.h
Purpose: This is Engine header file.
Project: CS225
Author: Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "Engine.h"

#define LIMITE_TIME 5

Engine::Engine() : mGameStateManager() {};

Engine::~Engine() {}

void Engine::Initialize(std::string windowName)
{
    mWindow.Initialize(windowName);
}

void Engine::Shutdown()
{
    mGameStateManager.Shutdown();
}

void  Engine::Update()
{
    now = std::chrono::system_clock::now();
    double dt = std::chrono::duration<double>(now - lastTick).count();
    sf::Event event;

    if (dt >= (1 / Engine::TargetFPS))
    {
        lastTick = now;
        timer += dt;
        ++frameCount;

        while (mWindow.GetWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Shutdown();
            }

            mInput.Update(event);
        }

        mWindow.Update();
        mGameStateManager.Update(dt);
    }

    if (timer >= LIMITE_TIME)
    {
        timer = 0;
        frameCount = 0;
    }
}

bool  Engine::HasGameEnded()
{
    return mGameStateManager.HasGameEnded();
}
