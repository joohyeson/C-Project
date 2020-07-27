/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Purpose: This is Level1 source file.
Project: CS225
Author: Daeun Jeong, Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "Level1.h"
#include "Engine.h" //Engine::GetWindow()
#include "Window.h"
#include "SFML/Window.hpp"
#include <time.h>
#include "Levels.h"
#include "Colors.h"

constexpr int FLAG = 11;
constexpr int MINE = 9;
constexpr int EMPTY = 0;
constexpr int TILE = 10;

Level1::Level1() {};

void Level1::Load()
{
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < 12; ++i)
    {
        std::vector<int> row;

        for (int j = 0; j < 12; ++j)
        {
            row.push_back(EMPTY);
        }

        mGrid.push_back(row);
    }

    for (int i = 0; i < 12; ++i)
    {
        std::vector<int> row;

        for (int j = 0; j < 12; ++j)
        {
            row.push_back(TILE);
        }

        mShowGrid.push_back(row);
    }

    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            if (rand() % 5 == 0)
            {
                mGrid[i][j] = MINE;
            }
        }
    }

    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            int numberOfMines = 0;

            if (mGrid[i][j] == MINE)
            {
                continue;
            }

            if (mGrid[i + 1][j] == MINE)
            {
                ++numberOfMines;
            }

            if (mGrid[i][j + 1] == MINE)
            {
                ++numberOfMines;
            }

            if (mGrid[i - 1][j] == MINE)
            {
                ++numberOfMines;
            }

            if (mGrid[i][j - 1] == MINE)
            {
                ++numberOfMines;
            }

            if (mGrid[i + 1][j + 1] == MINE)
            {
                ++numberOfMines;
            }

            if (mGrid[i - 1][j - 1] == MINE)
            {
                ++numberOfMines;
            }

            if (mGrid[i - 1][j + 1] == MINE)
            {
                ++numberOfMines;
            }

            if (mGrid[i + 1][j - 1] == MINE)
            {
                ++numberOfMines;
            }

            mGrid[i][j] = numberOfMines;
        }
    }

}

void Level1::Draw()
{
    Engine::GetWindow().Clear(sf::Color(LIGHT_BLUE));

    sf::Font font;
    font.loadFromFile("../Assets/Font/UhBee Se_hyun.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString("Minesweeper");
    text.setPosition(sf::Vector2f(0, 0));
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Regular);
    Engine::GetWindow().Draw(text);

    sf::Texture tileTexture;
    tileTexture.loadFromFile("../Assets/Art/tiles.jpg");
    sf::Sprite tileSprite(tileTexture);

    sf::Vector2i mousePosition = sf::Mouse::getPosition(Engine::GetWindow().GetWindow());

    int tileWidth = 32;
    int x = mousePosition.x / tileWidth;
    int y = mousePosition.y / tileWidth;

    if (mShouldGameRun == false)
    {
        text.setString("Game Over.. Press R key to restart.");
        text.setPosition(sf::Vector2f(0, 350));
        Engine::GetWindow().Draw(text);
    }

    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            if (0 <= x && x < 12 &&
                0 <= y && y < 12)
            {
                if (mShowGrid[x][y] == MINE)
                {
                    mShowGrid[i][j] = mGrid[i][j];
                    mShouldGameRun = false;
                }
            }

            tileSprite.setTextureRect(sf::IntRect(mShowGrid[i][j] * tileWidth, 0, tileWidth, tileWidth));

            tileSprite.setPosition(static_cast<float>(i) * static_cast<float>(tileWidth), static_cast<float>(j) * static_cast<float>(tileWidth));

            Engine::GetWindow().Draw(tileSprite);
        }
    }
}

void Level1::Update([[maybe_unused]] double dt)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(Engine::GetWindow().GetWindow());

    int tileWidth = 32;
    int x = mousePosition.x / tileWidth;
    int y = mousePosition.y / tileWidth;

    if (mShouldGameRun == true)
    {
        if (0 <= x && x < 12 &&
            0 <= y && y < 12)
        {
            if (Engine::GetInput().IsMousePressed(sf::Mouse::Left))
            {
                mShowGrid[x][y] = mGrid[x][y];
            }

            if (Engine::GetInput().IsMousePressed(sf::Mouse::Right))
            {
                mShowGrid[x][y] = FLAG;
            }

        }
    }

    if (Engine::GetInput().IsKeyPressed(sf::Keyboard::R))
    {
        Engine::GetGameStateManager().ReloadState();
        mShouldGameRun = true;
    }

    if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Space))
    {
        //Engine::GetGameStateManager().SetNextState(LEVEL2);
    }
}

void Level1::Unload()
{
    mGrid.clear();
    mShowGrid.clear();
}