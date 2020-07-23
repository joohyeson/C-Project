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

class Level2 : public GameState
{
public:
    Level2();
    void Load() override;
    void Update([[maybe_unused]]double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Level2"; }

private:
    bool mShouldGameRun = true;
};