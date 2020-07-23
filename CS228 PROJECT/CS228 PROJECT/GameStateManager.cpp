/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.cpp
Purpose: This is GameStateManager source file.
Project: CS280
Author: Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "Engine.h"
#include "GameStateManager.h"

void GameStateManager::AddGameState(std::unique_ptr<GameState> gameState)
{
    mGameStates.push_back(std::move(gameState));
}

void GameStateManager::Update(double dt)
{
    switch (mState)
    {
    case GameStateManager::State::START:
        SetStartState();
        break;

    case GameStateManager::State::LOAD:
        SetLoadState();
        break;

    case GameStateManager::State::RUNNING:
        SetRunningState(dt);
        break;

    case GameStateManager::State::UNLOAD:
        SetUnloadState();
        break;

    case GameStateManager::State::SHUTDOWN:
        SetShutDownState();
        break;

    default:
        break;
    }
}

void GameStateManager::SetNextState(int initState)
{
    mNextGameState = mGameStates.at(initState).get();
}

void GameStateManager::ReloadState()
{
    mState = State::UNLOAD;
}

void GameStateManager::Shutdown()
{
    mState = State::UNLOAD;
    mNextGameState = nullptr;
}

void GameStateManager::SetStartState()
{
    mNextGameState = mGameStates.at(0).get();
    mState = State::LOAD;
}

void GameStateManager::SetLoadState()
{
    mCurrentGameState = mNextGameState;

    mCurrentGameState->Load();
    mState = State::RUNNING;
}

void GameStateManager::SetRunningState(double dt)
{
    if (mCurrentGameState != mNextGameState)
    {
        mState = State::UNLOAD;
    }

    mCurrentGameState->Draw();

    mCurrentGameState->Update(dt);
}

void GameStateManager::SetUnloadState()
{
    mCurrentGameState->Unload();

    if (mNextGameState == nullptr)
    {
        mState = State::SHUTDOWN;
    }
    else
    {
        mState = State::LOAD;
    }
}

void GameStateManager::SetShutDownState()
{
    mState = State::EXIT;
}