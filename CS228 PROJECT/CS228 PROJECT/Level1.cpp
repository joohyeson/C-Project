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
#include <random>

constexpr int EMPTY = 0;
constexpr int MINE = 9;
constexpr int TILE = 10;
constexpr int FLAG = 11;
constexpr int GRID_LENGTH = 12;
constexpr int LEVEL = 8; // The higher is the easier.

std::vector<int> GetGridRow(void)
{
    std::vector<int> row(GRID_LENGTH, EMPTY);

    std::generate(row.begin() + 1, row.end() - 1,
        []()
    {
        if (rand() % LEVEL == 0)
        {
            return MINE;
        }
        return EMPTY;
    });

    return row;
}

std::vector<int> GetTileRow(void)
{
    return std::vector<int>(GRID_LENGTH, TILE);;
}

void Level1::Load()
{
    srand(static_cast<unsigned int>(time(0)));

    mGrid.resize(GRID_LENGTH);

    std::generate(mGrid.begin() + 1, mGrid.end() - 1, GetGridRow);

    mGrid.at(0) = std::vector<int>(GRID_LENGTH, EMPTY);
    mGrid.at(11) = std::vector<int>(GRID_LENGTH, EMPTY);

    mShowGrid.resize(GRID_LENGTH);
    std::generate(mShowGrid.begin(), mShowGrid.end(), GetTileRow);

    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            int numberOfMines = 0;

            std::vector<sf::Vector2i> checkLocation = { sf::Vector2i(0,1), sf::Vector2i(1,0), sf::Vector2i(0,-1), sf::Vector2i(-1,0), sf::Vector2i(-1,1), sf::Vector2i(-1,-1), sf::Vector2i(1,-1), sf::Vector2i(1,1) };

            for (int currCount = 0; currCount < checkLocation.size(); currCount++)
            {
                if (mGrid[i + checkLocation.at(currCount).x][j + checkLocation.at(currCount).y] == MINE)
                {
                    ++numberOfMines;
                }
            }

            if (mGrid[i][j] == MINE)
            {
                continue;
            }
            else
            {
                mGrid[i][j] = numberOfMines;
            }
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

void Level1::CanVisit(void)
{
    if (mToVisit.empty() != true)
    {
        mEmptyPlace.clear();

        while (mToVisit.empty() != true)
        {
            sf::Vector2i currentLocation = mToVisit.front();

            mToVisit.pop_front();
            mEmptyPlace.push_back(currentLocation);

            std::vector<sf::Vector2i> checkLocations = { sf::Vector2i(0,1), sf::Vector2i(1,0),sf::Vector2i(0,-1),sf::Vector2i(-1,0),sf::Vector2i(-1,1), sf::Vector2i(-1,-1),sf::Vector2i(1,-1),sf::Vector2i(1,1) };

            for (int i = 0; i < checkLocations.size(); ++i)
            {
                if (IsOutOfRange(currentLocation + checkLocations.at(i)) == false)
                {
                    if (TryToAdd(currentLocation + checkLocations.at(i)) == true)
                    {
                        mToVisit.push_back(currentLocation + checkLocations.at(i));
                    }
                }
            }
        }

        auto currentLocation = mEmptyPlace.begin();
        int count = 1;

        while (currentLocation != mEmptyPlace.end())
        {
            mShowGrid[currentLocation->x][currentLocation->y] = mGrid[currentLocation->x][currentLocation->y];

            currentLocation = mEmptyPlace.begin() + count;
            count++;
        }
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
    auto checkAlreadyExist = std::find(mEmptyPlace.begin(), mEmptyPlace.end(), location);

    if (checkAlreadyExist != mEmptyPlace.end())
    {
        return false;
    }

    if (mGrid[location.x][location.y] != EMPTY)
    {
        if (mGrid[location.x][location.y] != MINE)
        {
            mEmptyPlace.push_back(location);
        }

        return false;
    }

    if (mShowGrid[location.x][location.y] != TILE)
    {
        return false;
    }

    return true;
}

bool Level1::IsOutOfRange(sf::Vector2i location)
{
    if ((0 < location.x && location.x < GRID_LENGTH - 1) &&
        (0 < location.y && location.y < GRID_LENGTH - 1))
    {
        return false;
    }
    else
    {
        return true;
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
        if (IsOutOfRange(sf::Vector2i(x, y)) == false)
        {
            if (Engine::GetInput().IsMouseTriggered(sf::Mouse::Left))
            {
                Selected(sf::Vector2i(x, y));
                mShowGrid[x][y] = mGrid[x][y];
            }

            if (Engine::GetInput().IsMouseTriggered(sf::Mouse::Right))
            {
                if (mShowGrid[x][y] == TILE)
                {
                    mShowGrid[x][y] = FLAG;
                }
                else if (mShowGrid[x][y] == FLAG)
                {
                    mShowGrid[x][y] = TILE;
                }
            }

            CanVisit();
        }
    }

    if (Engine::GetInput().IsKeyTriggered(sf::Keyboard::R))
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