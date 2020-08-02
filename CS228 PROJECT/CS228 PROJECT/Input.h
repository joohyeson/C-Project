/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.hpp
Purpose: This is input header file.
Project: CS225
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
    void KeyUpdate();
    void ResetRelease();

private:
    bool mKeyPressed[sf::Keyboard::KeyCount];
    bool mKeyReleased[sf::Keyboard::KeyCount];
    bool mKeyTriggered[sf::Keyboard::KeyCount];

    bool mMousePressed[sf::Mouse::ButtonCount];
    bool mMouseReleased[sf::Mouse::ButtonCount];
    bool mMouseTriggered[sf::Mouse::ButtonCount];

    sf::Vector2i mMouse;
};