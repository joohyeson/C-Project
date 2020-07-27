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
#include <list> //std::list

class Level2 : public GameState
{
public:
    Level2();
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Level2"; }

private:
    bool mShouldGameRun = true;
    Player* mPlayer;
    std::list<GameObject*> mGameObjectList;
    Animation mBulletAnimation;
    Animation playerMoveAnimation;
    Animation playerAnimation;
    Animation explosionAnimation;
    Animation smallRockAnimation;
    Animation explosionShipAnimation;
    Animation rockAnimation;
};