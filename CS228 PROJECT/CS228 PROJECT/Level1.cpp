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
#include "Window.h"
#include "SFML/Window.hpp"
#include <time.h>

Level1::Level1() {};

void Level1::Load()
{
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            sgrid[i][j] = 10;
            if (rand() % 5 == 0)  grid[i][j] = 9;
            else grid[i][j] = 0;
        }

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            int n = 0;
            if (grid[i][j] == 9) continue;
            if (grid[i + 1][j] == 9) n++;
            if (grid[i][j + 1] == 9) n++;
            if (grid[i - 1][j] == 9) n++;
            if (grid[i][j - 1] == 9) n++;
            if (grid[i + 1][j + 1] == 9) n++;
            if (grid[i - 1][j - 1] == 9) n++;
            if (grid[i - 1][j + 1] == 9) n++;
            if (grid[i + 1][j - 1] == 9) n++;
            grid[i][j] = n;
        }

}

void Level1::Draw()
{
    Engine::GetWindow().Clear(sf::Color(51, 153, 218, 255));
    sf::Texture t;
    t.loadFromFile("../Assets/Art/tiles.jpg");
    sf::Sprite mSprite(t);

    sf::Vector2i pos = sf::Mouse::getPosition(Engine::GetWindow().GetWindow());
    int x = pos.x / w;
    int y = pos.y / w;

    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
        {
            if (sgrid[x][y] == 9) sgrid[i][j] = grid[i][j];
            mSprite.setTextureRect(sf::IntRect(sgrid[i][j] * w, 0, w, w));
            mSprite.setPosition(static_cast<float>(i) * static_cast<float>(w),
                static_cast<float>(j) * static_cast<float>(w));
            Engine::GetWindow().Draw(mSprite);
        }
}

void Level1::Update(double/* dt*/)
{
    sf::Vector2i pos = sf::Mouse::getPosition(Engine::GetWindow().GetWindow());
    int x = pos.x / w;
    int y = pos.y / w;

    if (Engine::GetInput().IsMousePressed(sf::Mouse::Left))
    {
        sgrid[x][y] = grid[x][y];
    }

    if (Engine::GetInput().IsMousePressed(sf::Mouse::Right))
    {
        sgrid[x][y] = 11;
    }
}

void Level1::Unload()
{
}