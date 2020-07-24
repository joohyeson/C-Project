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

#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
    Player();
    void Update() override;
    bool GetIsMoving();
    void SetIsMoving(bool newIsMoving);
private:
    bool isMoving;
};