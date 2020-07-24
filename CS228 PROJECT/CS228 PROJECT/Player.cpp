/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Player.h
Purpose: This is Player header file.
Project: CS280
Author: Daeun Jeong
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "Player.h"
#include "Engine.h" //Engine::GetWindow()

constexpr float DEGREE_TO_RADIAN = 0.017453f;

Player::Player()
{
    name = "player";
}

void Player::Update()
{
    if (isMoving == true)
    {
        dx += cos(angle * DEGREE_TO_RADIAN) * 0.2f;
        dy += sin(angle * DEGREE_TO_RADIAN) * 0.2f;
    }
    else
    {
        dx *= 0.99f;
        dy *= 0.99f;
    }

    float maxSpeed = 15.0f;

    float speed = sqrt(dx * dx + dy * dy);

    if (speed > maxSpeed)
    {
        dx *= maxSpeed / speed;
        dy *= maxSpeed / speed;
    }

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

bool Player::GetIsMoving()
{
    return isMoving;
}

void Player::SetIsMoving(bool newIsMoving)
{
    isMoving = newIsMoving;
}
