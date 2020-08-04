/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Window.h
Purpose: This is Window header file.
Project: CS225
Author: Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#pragma once
#include <SFML\Graphics\Color.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <iostream>

class Window
{
public:
    void Initialize(std::string windowName);
    void Update();
    void Resize(int newWidth, int newHeight);
    sf::Vector2u GetSize();
    sf::RenderWindow& GetWindow(void);
    void Draw(const sf::Drawable& drawable);
    void Clear(sf::Color color);

private:
    sf::RenderWindow mRenderWindow;
};