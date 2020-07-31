/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.h
Purpose: This is Level1 header file.
Project: CS225
Author: Daeun Jeong
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#pragma once
#include "GameState.h" //class Level1 : public GameState (Inheritance)
#include <vector> //std::vector
#include <list> //std::list

class Level1 : public GameState
{
public:
    Level1();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    bool CanVisit(void);
    void Selected(int x, int y);
    bool TryToAdd(int x, int y);

    std::string GetName() override { return "Level1"; }

private:
    std::vector<std::vector<int>> mGrid;
    std::vector<std::vector<int>> mShowGrid;

    std::list<sf::Vector2i> mToVisit;

    bool mShouldGameRun = true;
};