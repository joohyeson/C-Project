/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.h
Purpose: This is GameObject header file.
Project: CS225
Author: Daeun Jeong
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#pragma once
#include "SFML/Window.hpp" //sf::RenderWindow
#include "Animation.h" //Animation

class GameObject
{
public:
    GameObject() = default;
    void SetValues(const Animation& newAnimation, float newX, float newY, float newAngle = 0, float newRadius = 1);
    virtual void Update() {};
    void Draw(sf::RenderWindow& window);
    bool IsCollideWith(GameObject* object);
    virtual ~GameObject() {};

    float x, y, dx, dy, angle, radius;
    bool isAlive = true;
    std::string name;
    Animation animation;
};