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

#pragma once
#include "GameStateManager.h" //GameStateManager
#include "Input.h" //Input
#include "Window.h"
#include <string> //std::string
#include <chrono> //std::chrono::system_clock::time_point

class Engine
{
public:
    static Engine& Instance() { static Engine instance; return instance; }
    static Window& GetWindow() { return Instance().mWindow; }
    static Input& GetInput() { return Instance().mInput; }
    static GameStateManager& GetGameStateManager() { return Instance().mGameStateManager; }

    void Initialize(std::string windowName);
    void Shutdown();
    void Update();
    bool HasGameEnded();

private:
    Engine();
    ~Engine();

    GameStateManager mGameStateManager;
    Window mWindow;
    Input mInput;

    std::chrono::system_clock::time_point now, lastTick;
    static constexpr double TargetFPS = 30.0;
    double frameCount = 0;
    double timer = 0;
};