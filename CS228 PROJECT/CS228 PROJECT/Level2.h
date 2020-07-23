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
#include <list> //std::list

class Entity
{
public:
    Entity() {};
    void settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1);
    virtual void update() {};
    void draw(sf::RenderWindow& app);
    virtual ~Entity() {};

    float x, y, dx, dy, R, angle;
    bool life = true;
    std::string name;
    Animation anim;
};

class asteroid : public Entity
{
public:
    asteroid();
    void update() override;
};

class bullet : public Entity
{
public:
    bullet();
    void  update() override;
};


class player : public Entity
{
public:
    player();
    void update() override;
    bool thrust;
};

bool IsCollide(Entity* a, Entity* b);

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
    player* p;
    std::list<Entity*> entities;
    Animation sBullet;
};