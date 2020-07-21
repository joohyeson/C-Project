/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.h
Purpose: This is GameStateManager header file.
Project: CS280
Author: Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#pragma once
#include <vector> //std::vector
#include "GameState.h" //GameState* currGameState

class GameStateManager
{
public:
    GameStateManager();

    void AddGameState(GameState& gameState);
    void Update(double dt);
    void SetNextState(int initState);
    void Shutdown();
    void ReloadState();
    bool HasGameEnded() { return mState == State::EXIT; }

private:
    void SetStartState();
    void SetLoadState();
    void SetRunningState(double dt);
    void SetUnloadState();
    void SetShutDownState();

    enum class State
    {
        START,
        LOAD,
        RUNNING,
        UNLOAD,
        SHUTDOWN,
        EXIT,
    };

    std::vector<GameState*> mGameStates;
    State mState;
    GameState* mCurrentGameState;
    GameState* mNextGameState;
};

