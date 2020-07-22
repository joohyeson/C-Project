/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameState.h
Purpose: This is GameState header file.
Project: CS280
Author: Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#pragma once
#include <string> //std::string

class GameState
{
public:
    GameState() {};
    virtual void Load() = 0;
    virtual void Update(double dt) = 0;
    virtual void Unload() = 0;
    virtual void Draw() = 0;
    virtual std::string GetName() = 0;
    virtual ~GameState() {};
private:
};