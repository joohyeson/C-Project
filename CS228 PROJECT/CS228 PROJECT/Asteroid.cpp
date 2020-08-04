/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Asteroid.cpp
Purpose: This is Asteroid source file.
Project: CS225
Author: Daeun Jeong
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "Asteroid.h"
#include "Engine.h" //Engine::GetWindow()

Asteroid::Asteroid()
{
    dx = rand() % 8 - 4.0f;
    dy = rand() % 8 - 4.0f;
    name = "asteroid";
}

void Asteroid::Update()
{
    x += dx;
    y += dy;

    if (x > Engine::GetWindow().GetSize().x)
    {
        x = 0;
    }

    if (x < 0)
    {
        x = static_cast<float>(Engine::GetWindow().GetSize().x);
    }

    if (y > Engine::GetWindow().GetSize().y)
    {
        y = 0;
    }

    if (y < 0)
    {
        y = static_cast<float>(Engine::GetWindow().GetSize().y);
    }
}