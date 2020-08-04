/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.cpp
Purpose: This is GameObject source file.
Project: CS225
Author: Daeun Jeong, Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "GameObject.h"

void GameObject::SetValues(Animation& newAnimation, float newX, float newY, float newAngle, float newRadius)
{
    animation = &newAnimation;
    animation->SetOwner(this);
    x = newX;
    y = newY;
    angle = newAngle;
    radius = newRadius;
}

void GameObject::Draw(sf::RenderWindow& window)
{
    animation->GetAnimationSprite().setPosition(x, y);
    animation->GetAnimationSprite().setRotation(angle + 90.0f);
    window.draw(animation->GetAnimationSprite());

    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(255, 0, 0, 170));
    circle.setPosition(x, y);
    circle.setOrigin(radius, radius);
}

bool GameObject::IsCollideWith(GameObject* object)
{
    return (object->x - x) * (object->x - x) + (object->y - y) * (object->y - y) < (radius + object->radius) * (radius + object->radius);
}