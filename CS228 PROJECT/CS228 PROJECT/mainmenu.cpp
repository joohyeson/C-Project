/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainMenu.cpp
Purpose: This is MainMenu source file.
Project: CS280
Author: Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "MainMenu.h"
#include "Engine.h" //Engine::GetWindow()

MainMenu::MainMenu() {};

void MainMenu::Load()
{
    mFont.loadFromFile("../Assets/Font/UhBee Se_hyun.ttf");
}

void MainMenu::Draw()
{
    mMainMenuText.setFont(mFont);
    mMainMenuText.setString("Main Menu / Press space bar to go to the level 1.");
    mMainMenuText.setPosition(sf::Vector2f(0, 0));
    mMainMenuText.setCharacterSize(30);
    mMainMenuText.setStyle(sf::Text::Regular);

    Engine::GetWindow().Clear(sf::Color(51, 153, 218, 255));
    Engine::GetWindow().Draw(mMainMenuText);
}

void MainMenu::Update(double/* dt*/)
{
    if (Engine::GetInput().IsKeyTriggered(sf::Keyboard::Space) == true)
    {
        Engine::GetGameStateManager().SetNextState(LEVEL1);
    }
}

void MainMenu::Unload()
{
}