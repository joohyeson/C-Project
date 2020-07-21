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

    static void Update(sf::Event inputEvent);

    static bool IsKeyPressed(sf::Keyboard::Key scancode);
    static bool IsKeyReleased(sf::Keyboard::Key scancode);
    static bool IsKeyTriggered(sf::Keyboard::Key scancode);

    static bool IsMousePressed(sf::Mouse::Button mouseButton);
    static bool IsMouseReleased(sf::Mouse::Button mouseButton);
    static bool IsMouseTriggered(sf::Mouse::Button mouseButton);

    static sf::Vector2i GetMousePosition(void);

    static void Reset();

private:
    static void SetPressedKey(sf::Keyboard::Key scancode);
    static void SetReleasedKey(sf::Keyboard::Key scancode);

    static void SetPressedMouse(sf::Mouse::Button mouseButton);
    static void SetReleasedMouse(sf::Mouse::Button mouseButton);

    static void SetMousePosition(sf::Vector2i position);

    static std::bitset<sf::Keyboard::KeyCount> mKeyPressed;
    static std::bitset<sf::Keyboard::KeyCount> mKeyReleased;
    static std::bitset<sf::Keyboard::KeyCount> mKeyTriggered;

    static std::bitset<sf::Mouse::ButtonCount> mMousePressed;
    static std::bitset<sf::Mouse::ButtonCount> mMouseReleased;
    static std::bitset<sf::Mouse::ButtonCount> mMouseTriggered;

    static sf::Vector2i mMouse;
};