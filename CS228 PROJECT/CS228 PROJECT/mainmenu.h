/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: MainMenu.h
Purpose: This is MainMenu header file.
Project: CS225
Author: Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#pragma once
#include <SFML/Graphics.hpp> //sf::Font, sf::Text
#include "GameState.h" //class MainMenu : public GameState (Inheritance)
#include "Levels.h" //LEVEL1

class MainMenu : public GameState 
{
public:
    MainMenu();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "MainMenu"; }
};