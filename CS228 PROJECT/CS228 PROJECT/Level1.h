/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.h
Purpose: This is Level1 header file.
Project: CS280
Author: Daeun Jeong
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#pragma once
#include "GameState.h" //class Level1 : public GameState (Inheritance)
#include <SFML/Graphics.hpp> //sf::Font, sf::Text

class Level1 : public GameState 
{
public:
    Level1();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Level1"; }

private:
    sf::Font mFont;
    sf::Text mLevel1Text;

    int w = 32;
    int grid[12][12];
    int sgrid[12][12]; //for showing

    //sf::Sprite mSprite;
};