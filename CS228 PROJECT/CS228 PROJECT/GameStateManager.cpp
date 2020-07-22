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

GameStateManager::GameStateManager() : mCurrentGameState(nullptr), mNextGameState(nullptr), mState(State::START) { }

void GameStateManager::AddGameState(GameState& gameState)
{
    //std::unique_ptr<GameState> pGameState(&gameState);
    //mGameStates.push_back(pGameState);

    //std::unique_ptr<GameState> pGameState = std::make_unique<GameState>(gameState);
    //mGameStates.push_back(pGameState);

    mGameStates.push_back(&gameState);
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
    //mNextGameState = mGameStates.at(initState).get();
    mNextGameState = mGameStates.at(initState);
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
    //mNextGameState = mGameStates.at(0).get();
    mNextGameState = mGameStates.at(0);
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

    mCurrentGameState->Update(dt);

    mCurrentGameState->Draw();
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