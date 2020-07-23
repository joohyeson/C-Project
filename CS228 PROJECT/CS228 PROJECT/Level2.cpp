/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.cpp
Purpose: This is Level1 source file.
Project: CS280
Author: Daeun Jeong, Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "Level2.h"
#include "Engine.h" //Engine::GetWindow()
#include "Window.h"
#include "SFML/Window.hpp"

Level2::Level2() {};

void Level2::Load()
{
}

void Level2::Draw()
{
    Engine::GetWindow().Clear(sf::Color(51, 153, 218, 255));

    sf::Font font;
    font.loadFromFile("../Assets/Font/UhBee Se_hyun.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString("Asteroid");
    text.setPosition(sf::Vector2f(0, 0));
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Regular);
    Engine::GetWindow().Draw(text);

    if (mShouldGameRun == false)
    {
        text.setString("Game Over.. Press R key to restart.");
        text.setPosition(sf::Vector2f(0, 350));
        Engine::GetWindow().Draw(text);
    }
}

void Level2::Update([[maybe_unused]] double dt)
{
    if (Engine::GetInput().IsKeyPressed(sf::Keyboard::R))
    {
        Engine::GetGameStateManager().ReloadState();
        mShouldGameRun = true;
    }
}

void Level2::Unload()
{
}