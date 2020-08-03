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
#include <iostream>

constexpr int NUMBER_OF_ASTEROID = 7;
constexpr int NUMBER_OF_BULLETS = 150;
constexpr int RADIUS_OF_ASTEROID = 15;
constexpr float MOVING_ANGLE = 3.0f;

constexpr unsigned char IS_FIRING = 1 << 0;
constexpr unsigned char IS_MOVING = 1 << 0;

Level2::~Level2()
{
    Unload();
}

void Level2::DeepCopy(const Level2& rhs)
{
    mPlayer = new Player();
    auto object = rhs.mGameObjectList;

    for (auto objectList : object)
    {
        mGameObjectList.push_back(new GameObject(*objectList));
    }

    mIsGameOver = rhs.mIsGameOver;
    mIsGameCleared = rhs.mIsGameCleared;

    mPlayerSpriteFlags = rhs.mPlayerSpriteFlags;

    mBulletLimit = rhs.mBulletLimit;

    mBulletTimer = rhs.mBulletTimer;
    mPlayerMoveTimer = rhs.mPlayerMoveTimer;
}

Level2::Level2(const Level2& rhs)//copy constructor
{
    DeepCopy(rhs);
}

Level2::Level2(Level2&& rhs)//move constructor
{
    mIsGameOver = rhs.mIsGameOver;
    mIsGameCleared = rhs.mIsGameCleared;

    mPlayerSpriteFlags = rhs.mPlayerSpriteFlags;

    mBulletLimit = rhs.mBulletLimit;

    mBulletTimer = rhs.mBulletTimer;
    mPlayerMoveTimer = rhs.mPlayerMoveTimer;

    mPlayer = rhs.mPlayer;

    rhs.mPlayer = nullptr;
    rhs.mGameObjectList.clear();
}

Level2& Level2::operator=(const Level2& rhs)//copy assignment operator
{
    mGameObjectList.clear();
    DeepCopy(rhs);

    return *this;
}

Level2& Level2::operator=(Level2&& rhs)//move assignment operator
{
    if (this != &rhs)
    {
        mGameObjectList.clear();

        mIsGameOver = rhs.mIsGameOver;
        mIsGameCleared = rhs.mIsGameCleared;

        mPlayerSpriteFlags = rhs.mPlayerSpriteFlags;

        mBulletLimit = rhs.mBulletLimit;

        mBulletTimer = rhs.mBulletTimer;
        mPlayerMoveTimer = rhs.mPlayerMoveTimer;

        mPlayer = rhs.mPlayer;

        rhs.mPlayer = nullptr;
        rhs.mGameObjectList.clear();
    }

    return *this;
}

void Level2::Load()
{
    mIsGameOver = false;
    mIsGameCleared = false;

    mPlayerSpriteFlags = 0;

    mBulletLimit = NUMBER_OF_BULLETS;

    mBulletTimer = 0;
    mPlayerMoveTimer = 0;

    mPlayer = new Player();

    mPlayer->SetValues(Animation(eTexture::PLAYER), static_cast<float>(Engine::GetWindow().GetSize().x >> 1), static_cast<float>(Engine::GetWindow().GetSize().y >> 1), 0, 20);
    mGameObjectList.push_back(mPlayer);

    mPlayerOriginalScale = mPlayer->animation.GetAnimationSprite().getScale();
    mPlayerOriginalColor = mPlayer->animation.GetAnimationSprite().getColor();

    for (int i = 0; i < NUMBER_OF_ASTEROID; i++)
    {
        Asteroid* asteroid = new Asteroid();
        asteroid->SetValues(Animation(eTexture::ROCK), static_cast<float>(rand() % Engine::GetWindow().GetSize().x), static_cast<float>(rand() % Engine::GetWindow().GetSize().y), static_cast<float>(rand() % 360), 25);
        mGameObjectList.push_back(asteroid);
    }
}

void Level2::Draw()
{
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("../Assets/Art/background.jpg");
    backgroundTexture.setSmooth(true);
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

    if (mIsGameOver)
    {
        text.setString("Game Over.. Press R key to restart.");
        text.setPosition(sf::Vector2f(static_cast<float>(Engine::GetWindow().GetSize().x >> 1), static_cast<float>(Engine::GetWindow().GetSize().y >> 1)));
        Engine::GetWindow().Draw(text);
    }

    if (mIsGameCleared)
    {
        text.setString("Level Clear!");
        text.setPosition(sf::Vector2f(static_cast<float>(Engine::GetWindow().GetSize().x >> 1), static_cast<float>(Engine::GetWindow().GetSize().y >> 1)));
        Engine::GetWindow().Draw(text);
    }

    if (!mIsGameOver && !mIsGameCleared)
    {
        sf::String bulletInfo = "Number of bullets left : ";
        bulletInfo += std::to_string(mBulletLimit);
        text.setString(bulletInfo);
        text.setPosition(sf::Vector2f(static_cast<float>(Engine::GetWindow().GetSize().x >> 1), static_cast<float>(Engine::GetWindow().GetSize().y >> 1)));
        Engine::GetWindow().Draw(text);
    }
}

void Level2::Update([[maybe_unused]] double dt)
{
    if (mBulletTimer > 0.0f)
    {
        mBulletTimer -= static_cast<float>(dt);
    }

    if (mPlayerMoveTimer > 0.0f)
    {
        mPlayerMoveTimer -= static_cast<float>(dt);
    }

    if (!mIsGameOver)
    {
        for (auto objectAIterator = mGameObjectList.begin(); objectAIterator != mGameObjectList.end(); ++objectAIterator)
        {
            auto objectBIterator = objectAIterator;

            ++objectBIterator;

            for (; objectBIterator != mGameObjectList.end(); ++objectBIterator)
            {
                auto objectA = *objectAIterator;
                auto objectB = *objectBIterator;

                if (objectA->name == "asteroid" && objectB->name == "bullet")
                {
                    if (objectA->IsCollideWith(objectB))
                    {
                        objectA->isAlive = false;
                        objectB->isAlive = false;

                        GameObject* explosion = new GameObject();
                        explosion->SetValues(Animation(eTexture::EXPLOSION), objectA->x, objectA->y);
                        explosion->name = "explosion";
                        mGameObjectList.push_front(explosion);

                        for (int i = 0; i < 2; i++)
                        {
                            if (objectA->radius == RADIUS_OF_ASTEROID)
                            {
                                continue;
                            }
                            else
                            {
                                GameObject* asteroid = new Asteroid();
                                asteroid->SetValues(Animation(eTexture::SMALL_ROCK), objectA->x, objectA->y, static_cast<float>(rand() % 360), 15.0f);
                                mGameObjectList.push_front(asteroid);
                            }
                        }
                    }
                }

                if (objectA->name == "bullet" && objectB->name == "asteroid")
                {
                    if (objectB->IsCollideWith(objectA))
                    {
                        objectA->isAlive = false;
                        objectB->isAlive = false;

                        GameObject* explosion = new GameObject();
                        explosion->SetValues(Animation(eTexture::EXPLOSION), objectB->x, objectB->y);
                        explosion->name = "explosion";
                        mGameObjectList.push_front(explosion);

                        for (int i = 0; i < 2; i++)
                        {
                            if (objectB->radius == RADIUS_OF_ASTEROID)
                            {
                                continue;
                            }
                            else
                            {
                                GameObject* asteroid = new Asteroid();
                                asteroid->SetValues(Animation(eTexture::SMALL_ROCK), objectB->x, objectB->y, static_cast<float>(rand() % 360), 15.0f);
                                mGameObjectList.push_front(asteroid);
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
                        explosion->SetValues(Animation(eTexture::EXPLOSION), objectA->x, objectA->y);
                        explosion->name = "explosion";
                        mGameObjectList.push_front(explosion);

                        mPlayer->SetValues(Animation(eTexture::PLAYER), static_cast<float>(Engine::GetWindow().GetSize().x >> 1), static_cast<float>(Engine::GetWindow().GetSize().y >> 1), 0, 20);
                        mPlayer->dx = 0;
                        mPlayer->dy = 0;

                        mIsGameOver = true;
                    }
                }

                if (objectA->name == "asteroid" && objectB->name == "player")
                {
                    if (objectB->IsCollideWith(objectA))
                    {
                        objectA->isAlive = false;

                        GameObject* explosion = new GameObject();
                        explosion->SetValues(Animation(eTexture::EXPLOSION), objectB->x, objectB->y);
                        explosion->name = "explosion";
                        mGameObjectList.push_front(explosion);

                        mPlayer->SetValues(Animation(eTexture::PLAYER), static_cast<float>(Engine::GetWindow().GetSize().x >> 1), static_cast<float>(Engine::GetWindow().GetSize().y >> 1), 0, 20);
                        mPlayer->dx = 0;
                        mPlayer->dy = 0;

                        mIsGameOver = true;
                    }
                }
            }
        }

        for (auto objectIterator = mGameObjectList.begin(); objectIterator != mGameObjectList.end();)
        {
            GameObject* object = *objectIterator;

            object->Update();
            object->animation.Update();

            if (object->isAlive == false)
            {
                if (object->name == "Bullet")
                {
                    mBulletLimit++;
                }
                objectIterator = mGameObjectList.erase(objectIterator);
                delete object;
                object = nullptr;
            }
            else
            {
                objectIterator++;
            }
        }

        if (mPlayerSpriteFlags & IS_FIRING && mBulletTimer < 0.0f)
        {
            mPlayer->animation.GetAnimationSprite().setColor(static_cast<sf::Color>(RED));
            mBulletTimer = 0.3f;
        }
        else
        {
            mPlayer->animation.GetAnimationSprite().setColor(mPlayerOriginalColor);
        }

        if (mPlayerSpriteFlags & IS_MOVING && mPlayerMoveTimer < 0.0f)
        {
            mPlayer->animation.GetAnimationSprite().setScale(mPlayerOriginalScale.x, mPlayerOriginalScale.y + 50);
            mPlayerMoveTimer = 0.3f;
        }
        else
        {
            mPlayer->animation.GetAnimationSprite().setScale(mPlayerOriginalScale);
        }

        if (mPlayer->GetIsMoving() == true)
        {
            mPlayer->animation = Animation(eTexture::PLAYER_MOVE);
            mPlayerSpriteFlags |= IS_MOVING;
        }
        else
        {
            mPlayer->animation = Animation(eTexture::PLAYER);
            mPlayerSpriteFlags &= ~IS_MOVING;
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

        mIsGameCleared = true;

        for (auto asteroid : mGameObjectList)
        {
            if (asteroid->name == "asteroid")
            {
                mIsGameCleared = false;
            }
        }

        if (Engine::GetInput().IsKeyTriggered(sf::Keyboard::Space))
        {
            if (mBulletLimit > 0)
            {
                Bullet* bullet = new Bullet();
                bullet->SetValues(Animation(eTexture::BULLET), mPlayer->x, mPlayer->y, mPlayer->angle, 10.0f);
                mGameObjectList.push_front(bullet);
                mBulletLimit--;
                mPlayerSpriteFlags |= IS_FIRING;
            }
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

        for (auto object : mGameObjectList)
        {
            object->Draw(Engine::GetWindow().GetWindow());
        }
    }

    if (Engine::GetInput().IsKeyPressed(sf::Keyboard::R))
    {
        Engine::GetGameStateManager().ReloadState();
        mIsGameOver = false;
    }
}

void Level2::Unload()
{
    for (auto objectIterator = mGameObjectList.begin(); objectIterator != mGameObjectList.end(); objectIterator++)
    {
        auto temp = *objectIterator;
        delete temp;
    }
    mGameObjectList.clear();

    mPlayer = nullptr;
}