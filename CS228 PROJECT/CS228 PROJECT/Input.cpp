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
    mKeyPressed.reset();
    mKeyReleased.reset();
    mKeyTriggered.reset();

    mMousePressed.reset();
    mMouseReleased.reset();
    mMouseTriggered.reset();

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
    mKeyReleased = mKeyPressed;
    mMouseReleased = mMousePressed;
}

bool Input::IsKeyPressed(sf::Keyboard::Key scancode)
{
    return mKeyPressed[scancode];
}

bool Input::IsKeyReleased(sf::Keyboard::Key scancode)
{
    return mKeyPressed[scancode]==false;
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
    mMousePressed[mouseButton] = false;
    mMouseReleased[mouseButton] = true;
}

void Input::SetMousePosition(sf::Vector2i position)
{
    mMouse.x = position.x - static_cast<int>(Engine::GetWindow().GetSize().x >> 1);
    mMouse.y = -(position.y - static_cast<int>(Engine::GetWindow().GetSize().y >> 1));
}

void Input::Reset()
{
    mKeyReleased.reset();
    mKeyTriggered.reset();

    mMouseReleased.reset();
    mMouseTriggered.reset();
}

void Input::ResetRelease()
{
    mKeyReleased.reset();
}
