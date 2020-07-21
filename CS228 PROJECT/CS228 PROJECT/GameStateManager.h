#pragma once
#include <vector>
#include "GameState.h"

class GameStateManager
{
public:
    GameStateManager();

    void AddGameState(GameState& gameState);
    void Update(double dt);
    void SetNextState(int initState);
    void Shutdown();
    void ReloadState();
    bool HasGameEnded() { return state == State::EXIT; }

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

    std::vector<GameState*> gameStates;
    State state;
    GameState* currGameState;
    GameState* nextGameState;
};

