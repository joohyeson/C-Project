/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.h
Purpose: This is Level2 header file.
Project: CS280
Author: Daeun Jeong
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#pragma once
#include "GameState.h" //class Level2 : public GameState (Inheritance)
#include "SFML/Window.hpp" //sf::RenderWindow
#include "Animation.h" //Animation
#include <list> //std::list

class GameObject
{
public:
    GameObject() {};
    void SetValues(Animation& newAnimation, float newX, float newY, float newAngle = 0, float newRadius = 1);
    virtual void Update() {};
    void Draw(sf::RenderWindow& window);
    bool IsCollide(GameObject* a, GameObject* b);
    virtual ~GameObject() {};

    float x, y, dx, dy, radius, angle;
    bool isAlive = true;
    std::string name;
    Animation animation;
};

class Asteroid : public GameObject
{
public:
    Asteroid();
    void Update() override;
};

class Bullet : public GameObject
{
public:
    Bullet();
    void  Update() override;
};

class Player : public GameObject
{
public:
    Player();
    void Update() override;
    bool isMoving;
};


class Level2 : public GameState
{
public:
    Level2();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Level2"; }

private:
    bool mShouldGameRun = true;
    Player* mPlayer;
    std::list<GameObject*> mEntityList;
    Animation mBulletAnimation;
};