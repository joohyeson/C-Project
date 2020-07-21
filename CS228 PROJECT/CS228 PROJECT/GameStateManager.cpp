#include "Engine.h"
#include "GameStateManager.h"

GameStateManager::GameStateManager() : currGameState(nullptr), nextGameState(nullptr), state(State::START) { }

void GameStateManager::AddGameState(GameState& gameState) {
	gameStates.push_back(&gameState);

}

void GameStateManager::Update(double dt) {

	switch (state)
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

void GameStateManager::SetNextState(int initState) {
	nextGameState = gameStates[initState];
}

void GameStateManager::ReloadState() {
	state = State::UNLOAD;
}

void GameStateManager::Shutdown() {
	state = State::UNLOAD;
	nextGameState = nullptr;
}

void GameStateManager::SetStartState()
{
	nextGameState = gameStates[0];
	state = State::LOAD;
}

void GameStateManager::SetLoadState()
{
	currGameState = nextGameState;

	currGameState->Load();
	state = State::RUNNING;
}

void GameStateManager::SetRunningState(double dt)
{
	if (currGameState != nextGameState)
	{
		state = State::UNLOAD;
	}

	currGameState->Update(dt);

	currGameState->Draw();
}

void GameStateManager::SetUnloadState()
{
	currGameState->Unload();
	if (nextGameState == nullptr)
	{
		state = State::SHUTDOWN;
	}
	else
	{
		state = State::LOAD;
	}
}

void GameStateManager::SetShutDownState()
{
	state = State::EXIT;
}
