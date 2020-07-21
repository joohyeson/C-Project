/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.cpp
Purpose: This is input source file.
Project: CS280
Author: Daeun Jeong
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "Input.h"
#include "Engine.h" //Engine::GetWindow().GetSize()

std::bitset<sf::Keyboard::KeyCount> Input::mKeyPressed;
std::bitset<sf::Keyboard::KeyCount> Input::mKeyReleased;
std::bitset<sf::Keyboard::KeyCount> Input::mKeyTriggered;

std::bitset<sf::Mouse::ButtonCount> Input::mMousePressed;
std::bitset<sf::Mouse::ButtonCount> Input::mMouseReleased;
std::bitset<sf::Mouse::ButtonCount> Input::mMouseTriggered;

sf::Vector2i Input::mMouse;

Input::Input()
{
    mKeyPressed.reset();
    mKeyReleased.reset();
    mKeyTriggered.reset();

    mMousePressed.reset();
    mMouseReleased.reset();
    mMouseTriggered.reset();

    mMouse = sf::Vector2i(0, 0);
}

Input::~Input()
{
}

void Input::Update(sf::Event inputEvent)
{
    switch (inputEvent.type)
    {
    case sf::Event::EventType::KeyPressed:
        SetPressedKey(inputEvent.key.code);
        break;
    case sf::Event::EventType::KeyReleased:
        SetReleasedKey(inputEvent.key.code);
        break;
    case sf::Event::EventType::MouseMoved:
        SetMousePosition(sf::Vector2i(inputEvent.mouseButton.x, inputEvent.mouseButton.y));
        break;
    case sf::Event::EventType::MouseButtonPressed:
        SetPressedMouse(inputEvent.mouseButton.button);
        break;
    case sf::Event::EventType::MouseButtonReleased:
        SetReleasedMouse(inputEvent.mouseButton.button);
        break;
    default:
        break;
    }
}

bool Input::IsKeyPressed(sf::Keyboard::Key scancode)
{
    return mKeyPressed[scancode];
}

bool Input::IsKeyReleased(sf::Keyboard::Key scancode)
{
    return mKeyReleased[scancode];
}

bool Input::IsKeyTriggered(sf::Keyboard::Key scancode)
{
    return mKeyTriggered[scancode];
}

bool Input::IsMousePressed(sf::Mouse::Button mouseButton)
{
    return mMousePressed[mouseButton];
}

bool Input::IsMouseReleased(sf::Mouse::Button mouseButton)
{
    return mMouseReleased[mouseButton];
}

bool Input::IsMouseTriggered(sf::Mouse::Button mouseButton)
{
    return mMouseTriggered[mouseButton];
}

sf::Vector2i Input::GetMousePosition(void)
{
    return mMouse;
}

void Input::SetPressedKey(sf::Keyboard::Key scancode)
{
    if (mKeyPressed[scancode] != true)
    {
        mKeyPressed[scancode] = true;
        mKeyTriggered[scancode] = true;
    }
}

void Input::SetReleasedKey(sf::Keyboard::Key scancode)
{
    mKeyPressed[scancode] = false;
    mKeyReleased[scancode] = true;
}

void Input::SetPressedMouse(sf::Mouse::Button mouseButton)
{
    if (mMousePressed[mouseButton] != true)
    {
        mMousePressed[mouseButton] = true;
        mMouseTriggered[mouseButton] = true;
    }
}

void Input::SetReleasedMouse(sf::Mouse::Button mouseButton)
{
    mMousePressed[mouseButton] = false;
    mMouseReleased[mouseButton] = true;
}

void Input::SetMousePosition(sf::Vector2i position)
{
    mMouse.x = position.x - Engine::GetWindow().GetSize().x / 2.f;
    mMouse.y = -(position.y - Engine::GetWindow().GetSize().y / 2.f);
}

void Input::Reset()
{
    mKeyReleased.reset();
    mKeyTriggered.reset();

    mMouseReleased.reset();
    mMouseTriggered.reset();
}