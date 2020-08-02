/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.h
Purpose: This is Level2 header file.
Project: CS225
Author: Daeun Jeong
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#pragma once
#include "GameState.h" //class Level2 : public GameState (Inheritance)
#include "GameObject.h"
#include "Player.h"
#include "../CS225 List/List.h"

class Level2 : public GameState
{
public:
    Level2();
    ~Level2();

    Level2(const Level2& rhs); // copy constructor
    Level2(Level2&& rhs); // move constructor
    Level2& operator=(const Level2& rhs); // copy assignment
    Level2& operator=(Level2&& rhs); //move assignment

    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Level2"; }

private:
    unsigned char mFlags;
    int mBulletLimit;

    Player* mPlayer;

    List<GameObject*> mGameObjectList;

    Animation bulletAnimation;
    Animation playerMoveAnimation;
    Animation playerAnimation;
    Animation explosionAnimation;
    Animation smallRockAnimation;
    Animation explosionShipAnimation;
    Animation rockAnimation;

    sf::Texture shipTexture, explosionTexture, rockTexture, bulletTexture, smallRockTexture, explosionShipTexture, backgroundTexture;

    void DeepCopy(const Level2& rhs);
};