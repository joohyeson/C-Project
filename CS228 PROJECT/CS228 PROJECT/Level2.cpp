/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.cpp
Purpose: This is Level1 source file.
Project: CS225
Author: Daeun Jeong, Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "Level2.h"
#include "Engine.h" //Engine::GetWindow()
#include "Asteroid.h"
#include "Bullet.h"
#include "Colors.h"

constexpr int NUMBER_OF_ASTEROID = 7;
constexpr int RADIUS_OF_ASTEROID = 15;
constexpr float MOVING_ANGLE = 3.0f;

Level2::Level2() {}

void Level2::Load()
{
    shipTexture.loadFromFile("../Assets/Art/spaceship.png");
    backgroundTexture.loadFromFile("../Assets/Art/background.jpg");
    explosionTexture.loadFromFile("../Assets/Art/explosions/type_C.png");
    rockTexture.loadFromFile("../Assets/Art/rock.png");
    bulletTexture.loadFromFile("../Assets/Art/fire_blue.png");
    smallRockTexture.loadFromFile("../Assets/Art/rock_small.png");
    explosionShipTexture.loadFromFile("../Assets/Art/explosions/type_B.png");

    shipTexture.setSmooth(true);
    backgroundTexture.setSmooth(true);

    explosionAnimation = Animation(explosionTexture, 0, 0, 256, 256, 48, 0.5f);
    rockAnimation = Animation(rockTexture, 0, 0, 64, 64, 16, 0.2f);
    smallRockAnimation = Animation(smallRockTexture, 0, 0, 64, 64, 16, 0.2f);
    mBulletAnimation = Animation(bulletTexture, 0, 0, 32, 64, 16, 0.8f);
    playerAnimation = Animation(shipTexture, 40, 0, 40, 40, 1, 0.f);
    playerMoveAnimation = Animation(shipTexture, 40, 40, 40, 40, 1, 0.f);
    explosionShipAnimation = Animation(explosionShipTexture, 0, 0, 192, 192, 64, 0.5f);

    mPlayer = new Player();
    mPlayer->SetValues(playerAnimation, Engine::GetWindow().GetSize().x / 2.0f, Engine::GetWindow().GetSize().y / 2.0f, 0, 20);
    mGameObjectList.push_back(mPlayer);

    for (int i = 0; i < NUMBER_OF_ASTEROID; i++)
    {
        Asteroid* asteroid = new Asteroid();
        asteroid->SetValues(rockAnimation, static_cast<float>(rand() % Engine::GetWindow().GetSize().x), static_cast<float>(rand() % Engine::GetWindow().GetSize().y), static_cast<float>(rand() % 360), 25);
        mGameObjectList.push_back(asteroid);
    }
}

void Level2::Draw()
{
    sf::Sprite backgroundSprite(backgroundTexture);
    Engine::GetWindow().Draw(backgroundSprite);

    sf::Text text;
    text.setFont(Engine::GetGameStateManager().GetFont());
    text.setString("Asteroid");
    text.setPosition(sf::Vector2f(0, 0));
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Regular);
    Engine::GetWindow().Draw(text);

    srand(static_cast<unsigned int>(time(0)));

    Engine::GetWindow().GetWindow().setFramerateLimit(60);

    if (mShouldGameRun == false)
    {
        text.setString("Game Over.. Press R key to restart.");
        text.setPosition(sf::Vector2f(0, 350));
        Engine::GetWindow().Draw(text);
    }
}

void Level2::Update([[maybe_unused]] double dt)
{
    if (mShouldGameRun == true)
    {
        for (auto objectA : mGameObjectList)
        {
            for (auto objectB : mGameObjectList)
            {
                if (objectA->name == "asteroid" && objectB->name == "bullet")
                {
                    if (objectA->IsCollideWith(objectB))
                    {
                        objectA->isAlive = false;
                        objectB->isAlive = false;

                        GameObject* explosion = new GameObject();
                        explosion->SetValues(explosionAnimation, objectA->x, objectA->y);
                        explosion->name = "explosion";
                        mGameObjectList.push_back(explosion);

                        for (int i = 0; i < 2; i++)
                        {
                            if (objectA->radius == RADIUS_OF_ASTEROID)
                            {
                                continue;
                            }
                            else
                            {
                                GameObject* asteroid = new Asteroid();
                                asteroid->SetValues(smallRockAnimation, objectA->x, objectA->y, static_cast<float>(rand() % 360), 15.0f);
                                mGameObjectList.push_back(asteroid);
                            }
                        }
                    }
                }

                if (objectA->name == "player" && objectB->name == "asteroid")
                {
                    if (objectA->IsCollideWith(objectB))
                    {
                        objectB->isAlive = false;

                        GameObject* explosion = new GameObject();
                        explosion->SetValues(explosionAnimation, objectA->x, objectA->y);
                        explosion->name = "explosion";
                        mGameObjectList.push_back(explosion);

                        mPlayer->SetValues(playerAnimation, Engine::GetWindow().GetSize().x / 2.0f, Engine::GetWindow().GetSize().y / 2.0f, 0, 20);
                        mPlayer->dx = 0;
                        mPlayer->dy = 0;

                        mShouldGameRun = false;
                    }
                }
            }
        }

        if (mPlayer->GetIsMoving() == true)
        {
            mPlayer->animation = playerMoveAnimation;
        }
        else
        {
            mPlayer->animation = playerAnimation;
        }

        for (auto explosion : mGameObjectList)
        {
            if (explosion->name == "explosion")
            {
                if (explosion->animation.IsAnimationEnded())
                {
                    explosion->isAlive = false;
                }
            }
        }

        for (auto object : mGameObjectList)
        {
            object->Draw(Engine::GetWindow().GetWindow());
        }

        for (auto objectIterator = mGameObjectList.begin(); objectIterator != mGameObjectList.end();)
        {
            GameObject* object = *objectIterator;

            object->Update();
            object->animation.Update();

            if (object->isAlive == false)
            {
                objectIterator = mGameObjectList.erase(objectIterator);
                delete object;
            }
            else
            {
                objectIterator++;
            }
        }

        if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Space))
        {
            Bullet* bullet = new Bullet();
            bullet->SetValues(mBulletAnimation, mPlayer->x, mPlayer->y, mPlayer->angle, 10.0f);
            mGameObjectList.push_back(bullet);
        }

        if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Right))
        {
            mPlayer->angle += MOVING_ANGLE;
        }

        if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Left))
        {
            mPlayer->angle -= MOVING_ANGLE;
        }

        if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Up))
        {
            mPlayer->SetIsMoving(true);
        }
        else
        {
            mPlayer->SetIsMoving(false);
        }
    }

    if (Engine::GetInput().IsKeyPressed(sf::Keyboard::R))
    {
        Engine::GetGameStateManager().ReloadState();
        mShouldGameRun = true;
    }
}

void Level2::Unload()
{
    mGameObjectList.clear();
    mPlayer = nullptr;
}