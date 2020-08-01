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
#include "Levels.h"
#include "Colors.h"
#include <time.h>
#include <algorithm>

constexpr int EMPTY = 0;
constexpr int MINE = 9;
constexpr int TILE = 10;
constexpr int FLAG = 11;
constexpr int GRID_LENGTH = 12;
constexpr int LEVEL = 10; // The higher is the easier.

Level1::Level1() {};

constexpr int Empty(void)
{
    return EMPTY;
}

std::vector<int> EmptyRow(void)
{
    std::vector<int> row;
    row.resize(GRID_LENGTH);
    std::generate(row.begin(), row.end(), Empty);

    return row;
}

constexpr int Tile(void)
{
    return TILE;
}

std::vector<int> TileRow(void)
{
    std::vector<int> row;
    row.resize(GRID_LENGTH);
    std::generate(row.begin(), row.end(), Tile);

    return row;
}

void Level1::Load()
{
    srand(static_cast<unsigned int>(time(0)));

    mGrid.resize(GRID_LENGTH);
    std::generate(mGrid.begin(), mGrid.end(), EmptyRow);

    mShowGrid.resize(GRID_LENGTH);
    std::generate(mShowGrid.begin(), mShowGrid.end(), TileRow);

    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            if (rand() % LEVEL == 0)
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

    sf::Text text;
    text.setFont(Engine::GetGameStateManager().GetFont());
    text.setString("Minesweeper");
    text.setPosition(sf::Vector2f(0, 0));
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Regular);
    Engine::GetWindow().Draw(text);

    //sf::Text text2;
    //text2.setFont(Engine::GetGameStateManager().GetFont());
    //text2.setString("Hint Count :" + std::to_string(mHintCount));
    //text2.setPosition(sf::Vector2f(800, 0));
    //text2.setCharacterSize(30);
    //text2.setStyle(sf::Text::Regular);
    //Engine::GetWindow().Draw(text2);

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
            if (IsOutOfRange(sf::Vector2i(x, y)) == false)
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

bool Level1::CanVisit(void)
{
    if (mToVisit.empty() == true)
    {
        return true;
    }
    else
    {
        mEmptyPlace.clear();

        while (mToVisit.empty() != true)
        {
            sf::Vector2i currentLocation = mToVisit.front();

            mToVisit.pop_front();
            mEmptyPlace.push_back(currentLocation);

            sf::Vector2i above = { currentLocation.x, currentLocation.y + 1 };
            sf::Vector2i right = { currentLocation.x + 1, currentLocation.y };
            sf::Vector2i below = { currentLocation.x, currentLocation.y - 1 };
            sf::Vector2i left = { currentLocation.x - 1, currentLocation.y };

            if (IsOutOfRange(above) == false)
            {
                if (TryToAdd(above) == true)
                {
                    mToVisit.push_back(above);
                }
            }

            if (IsOutOfRange(right) == false)
            {
                if (TryToAdd(right) == true)
                {
                    mToVisit.push_back(right);
                }
            }

            if (IsOutOfRange(below) == false)
            {
                if (TryToAdd(below) == true)
                {
                    mToVisit.push_back(below);
                }
            }

            if (IsOutOfRange(left) == false)
            {
                if (TryToAdd(left) == true)
                {
                    mToVisit.push_back(left);
                }
            }
        }

        for (auto emptyLocation : mEmptyPlace)
        {
            mShowGrid[emptyLocation.x][emptyLocation.y] = EMPTY;
        }

        return false;
    }
}

void Level1::Selected(sf::Vector2i location)
{
    mToVisit.clear();

    if (mGrid[location.x][location.y] != EMPTY)
    {
        return;
    }
    else
    {
        mToVisit.push_back(location);
    }
}

bool Level1::TryToAdd(sf::Vector2i location)
{
    std::vector<sf::Vector2i>::iterator checkAlreadyExist = std::find(mEmptyPlace.begin(), mEmptyPlace.end(), location);

    if (checkAlreadyExist != mEmptyPlace.end())
    {
        return false;
    }

    if (mGrid[location.x][location.y] != EMPTY)
    {
        return false;
    }

    return true;
}

bool Level1::IsOutOfRange(sf::Vector2i location)
{
    if ((0 <= location.x && location.x < GRID_LENGTH) &&
        (0 <= location.y && location.y < GRID_LENGTH))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Level1::ShowHint(void)
{
}

void Level1::Update([[maybe_unused]] double dt)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(Engine::GetWindow().GetWindow());

    int tileWidth = 32;
    int x = mousePosition.x / tileWidth;
    int y = mousePosition.y / tileWidth;

    if (mShouldGameRun == true)
    {
        if (IsOutOfRange(sf::Vector2i(x, y)) == false)
        {
            if (Engine::GetInput().IsMousePressed(sf::Mouse::Left))
            {
                Selected(sf::Vector2i(x, y));
                mShowGrid[x][y] = mGrid[x][y];
            }

            if (Engine::GetInput().IsMousePressed(sf::Mouse::Right))
            {
                mShowGrid[x][y] = FLAG;
            }

            CanVisit();
        }
    }

    if (Engine::GetInput().IsKeyTriggered(sf::Keyboard::H))
    {
        ShowHint();
    }

    if (Engine::GetInput().IsKeyPressed(sf::Keyboard::R))
    {
        Engine::GetGameStateManager().ReloadState();
        mShouldGameRun = true;
    }

    if (Engine::GetInput().IsKeyTriggered(sf::Keyboard::Space))
    {
        Engine::GetGameStateManager().SetNextState(LEVEL2);
    }

    if (Engine::GetInput().IsKeyTriggered(sf::Keyboard::Escape) == true)
    {
        Engine::GetGameStateManager().Shutdown();
    }
}

void Level1::Unload()
{
    mGrid.clear();
    mShowGrid.clear();
}