/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: main.cpp
Purpose: This is main source file.
Project: CS280
Author: Daeun Jeong, Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "Engine.h" //Engine::Instance();
#include "MainMenu.h" //MainMenu
#include "Level1.h" //Level1
#include "Level2.h" //Level2


int main()
{
    Engine& engine = Engine::Instance();

    engine.Initialize("PROJECT");

    engine.GetGameStateManager().AddGameState<MainMenu>();
    engine.GetGameStateManager().AddGameState<Level1>();
    engine.GetGameStateManager().AddGameState<Level2>();

    while (engine.HasGameEnded() == false)
    {
        engine.Update();
    }

    engine.Shutdown();

    return 0;
}