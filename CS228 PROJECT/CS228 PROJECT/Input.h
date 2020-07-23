/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.hpp
Purpose: This is input header file.
Project: CS280
Author: Daeun Jeong
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#pragma once
#include <SFML/Graphics.hpp> //sf::Keyboard::Key, sf::Mouse
#include <bitset> //std::bitset

class Input
{
public:
    Input();
    ~Input();

    void Update(sf::Event inputEvent);

    bool IsKeyPressed(sf::Keyboard::Key scancode);
    bool IsKeyReleased(sf::Keyboard::Key scancode);
    bool IsKeyTriggered(sf::Keyboard::Key scancode);

    bool IsMousePressed(sf::Mouse::Button mouseButton);
    bool IsMouseReleased(sf::Mouse::Button mouseButton);
    bool IsMouseTriggered(sf::Mouse::Button mouseButton);

    void SetPressedKey(sf::Keyboard::Key scancode);
    void SetReleasedKey(sf::Keyboard::Key scancode);

    void SetPressedMouse(sf::Mouse::Button mouseButton);
    void SetReleasedMouse(sf::Mouse::Button mouseButton);

    void SetMousePosition(sf::Vector2i position);

    sf::Vector2i GetMousePosition(void);

    void Reset();

private:
    std::bitset<sf::Keyboard::KeyCount> mKeyPressed;
    std::bitset<sf::Keyboard::KeyCount> mKeyReleased;
    std::bitset<sf::Keyboard::KeyCount> mKeyTriggered;

    std::bitset<sf::Mouse::ButtonCount> mMousePressed;
    std::bitset<sf::Mouse::ButtonCount> mMouseReleased;
    std::bitset<sf::Mouse::ButtonCount> mMouseTriggered;

    sf::Vector2i mMouse;
};