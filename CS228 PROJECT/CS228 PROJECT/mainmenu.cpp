/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainMenu.cpp
Purpose: This is MainMenu source file.
Project: CS225
Author: Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "MainMenu.h"
#include "Engine.h" //Engine::GetWindow()

MainMenu::MainMenu() {};

void MainMenu::Load()
{
}

void MainMenu::Draw()
{
    sf::Text mainMenuText;
    mainMenuText.setFont(Engine::GetGameStateManager().GetFont());
    mainMenuText.setString("Main Menu / Press space bar to go to the level 1.");
    mainMenuText.setPosition(sf::Vector2f(0, 0));
    mainMenuText.setCharacterSize(30);
    mainMenuText.setStyle(sf::Text::Regular);

    Engine::GetWindow().Clear(sf::Color(51, 153, 218, 255));
    Engine::GetWindow().Draw(mainMenuText);
}

void MainMenu::Update(double/* dt*/)
{
    if (Engine::GetInput().IsKeyReleased(sf::Keyboard::Space) == true)
    {
        
        Engine::GetGameStateManager().SetNextState(LEVEL1);
    }

    if (Engine::GetInput().IsKeyReleased(sf::Keyboard::F))
    {
       std::cout << "F" << std::endl;
       Engine::GetWindow().SetFullScreen();
    }

    if (Engine::GetInput().IsKeyReleased(sf::Keyboard::Escape) == true)
    {
        Engine::GetGameStateManager().Shutdown();
    }
}

void MainMenu::Unload()
{
}