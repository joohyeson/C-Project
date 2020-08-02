/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input.cpp
Purpose: This is input source file.
Project: CS225
Author: Daeun Jeong
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "Input.h"
#include "Engine.h" //Engine::GetWindow().GetSize()

Input::Input()
{
    Reset();

    mMouse = sf::Vector2i(0, 0);
}

Input::~Input() {}

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

void Input::KeyUpdate()
{
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
    {
        mKeyReleased[i] = mKeyPressed[i];
    }

    for (int i = 0; i < sf::Mouse::ButtonCount; ++i)
    {
        mMouseReleased[i] = mMousePressed[i];
    }
}

bool Input::IsKeyPressed(sf::Keyboard::Key scancode)
{
    return mKeyPressed[scancode];
}

bool Input::IsKeyReleased(sf::Keyboard::Key scancode)
{
    return mKeyPressed[scancode] == false;
}

bool Input::IsKeyTriggered(sf::Keyboard::Key scancode)
{
    return mKeyPressed[scancode] == true && mKeyReleased[scancode] == false;
}

bool Input::IsMousePressed(sf::Mouse::Button mouseButton)
{
    return mMousePressed[mouseButton];
}

bool Input::IsMouseReleased(sf::Mouse::Button mouseButton)
{
    return mMousePressed[mouseButton] == false;
}

bool Input::IsMouseTriggered(sf::Mouse::Button mouseButton)
{
    return  mMousePressed[mouseButton] == true && mMouseReleased[mouseButton] == false;
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
    }
}

void Input::SetReleasedKey(sf::Keyboard::Key scancode)
{
    if (mKeyReleased[scancode] != true)
    {
        mKeyReleased[scancode] = true;
    }

    mKeyPressed[scancode] = false;

}

void Input::SetPressedMouse(sf::Mouse::Button mouseButton)
{
    if (mMousePressed[mouseButton] != true)
    {
        mMousePressed[mouseButton] = true;
    }
}

void Input::SetReleasedMouse(sf::Mouse::Button mouseButton)
{
    if (mMouseReleased[mouseButton] != true)
    {
        mMouseReleased[mouseButton] = true;
    }

    mMousePressed[mouseButton] = false;
}

void Input::SetMousePosition(sf::Vector2i position)
{
    mMouse.x = position.x - static_cast<int>(Engine::GetWindow().GetSize().x >> 1);
    mMouse.y = -(position.y - static_cast<int>(Engine::GetWindow().GetSize().y >> 1));
}

void Input::Reset()
{
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
    {
        mKeyPressed[i] = 0;
        mKeyReleased[i] = 0;
        mKeyTriggered[i] = 0;
    }

    for (int i = 0; i < sf::Mouse::ButtonCount; ++i)
    {
        mMousePressed[i] = 0;
        mMouseReleased[i] = 0;
        mMouseTriggered[i] = 0;
    }
}

void Input::ResetRelease()
{
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
    {
        mKeyReleased[i] = 0;
    }
}