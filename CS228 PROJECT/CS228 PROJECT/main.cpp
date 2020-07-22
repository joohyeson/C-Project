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

int main()
{
    Engine& engine = Engine::Instance();

    //try 
    //{
        engine.Initialize("PROJECT");
        MainMenu mainMenu;
        Level1 level1;

        engine.GetGameStateManager().AddGameState(mainMenu);
        engine.GetGameStateManager().AddGameState(level1);

        while (engine.HasGameEnded() == false) 
        {
            engine.Update();
        }

        engine.Shutdown();
        
        return 0;
    //}
    //catch (std::exception& e) 
    //{
    //    return -1;
    //}
}