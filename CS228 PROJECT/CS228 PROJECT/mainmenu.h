
#pragma once
#include "GameState.h"

class MainMenu : public GameState {
public:
	MainMenu();
	void Load() override;
	void Update(double dt) override;
	void Unload() override;
	void Draw() override;

	std::string GetName() override { return "MainMenu"; }

};