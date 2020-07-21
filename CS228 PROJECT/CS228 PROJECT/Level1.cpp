/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Purpose: This is Level1 source file.
Project: CS280
Author: Daeun Jeong
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "Level1.h"
#include "Engine.h" //Engine::GetWindow()

Level1::Level1() {};

void Level1::Load()
{
    mFont.loadFromFile("../Assets/Font/UhBee Se_hyun.ttf");
}

void Level1::Draw()
{
    mLevel1Text.setFont(mFont);
    mLevel1Text.setString("Level1");
    mLevel1Text.setPosition(sf::Vector2f(0, 0));
    mLevel1Text.setCharacterSize(30);
    mLevel1Text.setStyle(sf::Text::Regular);

    Engine::GetWindow().Clear(sf::Color(100, 50, 50, 255));
    Engine::GetWindow().Draw(mLevel1Text);
}

void Level1::Update(double/* dt*/)
{
}

void Level1::Unload()
{
}