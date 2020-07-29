/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.h
Purpose: This is GameStateManager header file.
Project: CS225
Author: Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#pragma once
#include <vector> //std::vector
#include <memory> //std::unique_ptr
#include "GameState.h" //GameState* currGameState
#include "SFML/Graphics.hpp" //sf::Font

class GameStateManager
{
public:
    void AddGameState(std::unique_ptr<GameState> gameState);
    template<typename GAME_STATE>
    void AddGameState();
    void Update(double dt);
    void SetNextState(int initState);
    void Shutdown();
    void ReloadState();
    bool HasGameEnded() { return mState == State::EXIT; }
    sf::Font& GetFont(void);

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

    std::vector<std::unique_ptr<GameState>> mGameStates{};

    State mState = State::START;
    GameState* mCurrentGameState = nullptr;
    GameState* mNextGameState = nullptr;

    sf::Font mFont;
};

template <typename GAME_STATE>
void GameStateManager::AddGameState()
{
    mGameStates.push_back(std::make_unique<GAME_STATE>());
}