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
constexpr unsigned char IS_MOVING = 1 << 1;

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

    bulletTexture = rhs.bulletTexture;
    playerTexture = rhs.playerTexture;
    playerMoveTexture = rhs.playerMoveTexture;
    explosionTexture = rhs.explosionTexture;
    rockTexture = rhs.rockTexture;
    smallRockTexture = rhs.smallRockTexture;
    backgroundTexture = rhs.backgroundTexture;

    backgroundSprite = rhs.backgroundSprite;

    bulletAnimation = rhs.bulletAnimation;
    playerAnimation = rhs.playerAnimation;
    playerMoveAnimation = rhs.playerAnimation;
    explosionAnimation = rhs.explosionAnimation;
    rockAnimation = rhs.rockAnimation;
    smallRockAnimation = rhs.smallRockAnimation;
}

Level2::Level2(const Level2& rhs)
{
    DeepCopy(rhs);
}

Level2::Level2(Level2&& rhs)
{
    mIsGameOver = rhs.mIsGameOver;
    mIsGameCleared = rhs.mIsGameCleared;

    mPlayerSpriteFlags = rhs.mPlayerSpriteFlags;

    mBulletLimit = rhs.mBulletLimit;

    mBulletTimer = rhs.mBulletTimer;
    mPlayerMoveTimer = rhs.mPlayerMoveTimer;

    bulletTexture = rhs.bulletTexture;
    playerTexture = rhs.playerTexture;
    playerMoveTexture = rhs.playerMoveTexture;
    explosionTexture = rhs.explosionTexture;
    rockTexture = rhs.rockTexture;
    smallRockTexture = rhs.smallRockTexture;
    backgroundTexture = rhs.backgroundTexture;

    backgroundSprite = rhs.backgroundSprite;

    bulletAnimation = rhs.bulletAnimation;
    playerAnimation = rhs.playerAnimation;
    playerMoveAnimation = rhs.playerAnimation;
    explosionAnimation = rhs.explosionAnimation;
    rockAnimation = rhs.rockAnimation;
    smallRockAnimation = rhs.smallRockAnimation;

    mPlayer = rhs.mPlayer;
    rhs.mPlayer = nullptr;

    mGameObjectList = std::move(rhs.mGameObjectList);
}

Level2& Level2::operator=(const Level2& rhs)
{
    Unload();

    DeepCopy(rhs);

    return *this;
}

Level2& Level2::operator=(Level2&& rhs)
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

        bulletTexture = rhs.bulletTexture;
        playerTexture = rhs.playerTexture;
        playerMoveTexture = rhs.playerMoveTexture;
        explosionTexture = rhs.explosionTexture;
        rockTexture = rhs.rockTexture;
        smallRockTexture = rhs.smallRockTexture;
        backgroundTexture = rhs.backgroundTexture;

        backgroundSprite = rhs.backgroundSprite;

        bulletAnimation = rhs.bulletAnimation;
        playerAnimation = rhs.playerAnimation;
        playerMoveAnimation = rhs.playerAnimation;
        explosionAnimation = rhs.explosionAnimation;
        rockAnimation = rhs.rockAnimation;
        smallRockAnimation = rhs.smallRockAnimation;

        mPlayer = rhs.mPlayer;
        rhs.mPlayer = nullptr;

        mGameObjectList = std::move(rhs.mGameObjectList);
        rhs.mGameObjectList.clear();
    }

    return *this;
}

Animation Level2::LoadAnimation(eLevel2Texture textureEnum)
{
    switch (textureEnum)
    {
    case eLevel2Texture::BULLET:
        bulletTexture.loadFromFile("../Assets/Art/fire_blue.png");
        return Animation(bulletTexture, 0, 0, 32, 64, 16, 0.8f);
        break;
    case eLevel2Texture::PLAYER:
        playerTexture.loadFromFile("../Assets/Art/spaceship.png");
        playerTexture.setSmooth(true);
        return Animation(playerTexture, 40, 0, 40, 40, 1, 0.f);
        break;
    case eLevel2Texture::PLAYER_MOVE:
        playerMoveTexture.loadFromFile("../Assets/Art/spaceship.png");
        playerMoveTexture.setSmooth(true);
        return Animation(playerMoveTexture, 40, 40, 40, 40, 1, 0.f);
        break;
    case eLevel2Texture::EXPLOSION:
        explosionTexture.loadFromFile("../Assets/Art/type_C.png");
        return Animation(explosionTexture, 0, 0, 256, 256, 48, 0.3f);
        break;
    case eLevel2Texture::ROCK:
        rockTexture.loadFromFile("../Assets/Art/rock.png");
        return Animation(rockTexture, 0, 0, 64, 64, 16, 0.1f);
        break;
    case eLevel2Texture::SMALL_ROCK:
        smallRockTexture.loadFromFile("../Assets/Art/rock_small.png");
        return Animation(smallRockTexture, 0, 0, 64, 64, 16, 0.1f);
        break;
    default:
        break;
    }

    return Animation();
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

    bulletAnimation = LoadAnimation(eLevel2Texture::BULLET);
    playerAnimation = LoadAnimation(eLevel2Texture::PLAYER);
    playerMoveAnimation = LoadAnimation(eLevel2Texture::PLAYER_MOVE);
    explosionAnimation = LoadAnimation(eLevel2Texture::EXPLOSION);
    rockAnimation = LoadAnimation(eLevel2Texture::ROCK);
    smallRockAnimation = LoadAnimation(eLevel2Texture::SMALL_ROCK);

    backgroundTexture.loadFromFile("../Assets/Art/background.jpg");
    backgroundTexture.setSmooth(true);
    backgroundSprite.setTexture(backgroundTexture);

    mPlayer->SetValues(playerAnimation, static_cast<float>(Engine::GetWindow().GetSize().x >> 1), static_cast<float>(Engine::GetWindow().GetSize().y >> 1), 0, 20);
    mGameObjectList.push_back(mPlayer);

    mPlayerOriginalScale = mPlayer->animation->GetAnimationSprite().getScale();
    mPlayerOriginalColor = mPlayer->animation->GetAnimationSprite().getColor();

    for (int i = 0; i < NUMBER_OF_ASTEROID; i++)
    {
        Asteroid* asteroid = new Asteroid();
        asteroid->SetValues(rockAnimation, static_cast<float>(rand() % Engine::GetWindow().GetSize().x), static_cast<float>(rand() % Engine::GetWindow().GetSize().y), static_cast<float>(rand() % 360), 25);
        mGameObjectList.push_back(asteroid);
    }
}

void Level2::Draw()
{
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

                if (objectA->name == "bullet" && objectB->name == "asteroid")
                {
                    if (objectB->IsCollideWith(objectA))
                    {
                        objectA->isAlive = false;
                        objectB->isAlive = false;

                        GameObject* explosion = new GameObject();
                        explosion->SetValues(explosionAnimation, objectB->x, objectB->y);
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
                                asteroid->SetValues(smallRockAnimation, objectB->x, objectB->y, static_cast<float>(rand() % 360), 15.0f);
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
                        explosion->SetValues(explosionAnimation, objectA->x, objectA->y);
                        explosion->name = "explosion";
                        mGameObjectList.push_front(explosion);

                        mPlayer->SetValues(playerAnimation, static_cast<float>(Engine::GetWindow().GetSize().x >> 1), static_cast<float>(Engine::GetWindow().GetSize().y >> 1), 0, 20);
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
            object->animation->Update();

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

        if (mPlayer->GetIsMoving() == true)
        {
            mPlayer->animation = &playerMoveAnimation;
            mPlayerSpriteFlags |= IS_MOVING;
        }
        else
        {
            mPlayer->animation = &playerAnimation;
            mPlayerSpriteFlags &= ~IS_MOVING;
        }

        for (auto explosion : mGameObjectList)
        {
            if (explosion->name == "explosion")
            {
                if (explosion->animation->IsAnimationEnded())
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
                bullet->SetValues(bulletAnimation, mPlayer->x, mPlayer->y, mPlayer->angle, 10.0f);
                mGameObjectList.push_front(bullet);
                mBulletLimit--;
                mPlayerSpriteFlags |= IS_FIRING;
                mBulletTimer = 1.0f;
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

        if (mPlayerSpriteFlags & IS_FIRING && mBulletTimer > 0.0f)
        {
            mPlayer->animation->GetAnimationSprite().setColor(static_cast<sf::Color>(BLUE));
        }
        else
        {
            mPlayer->animation->GetAnimationSprite().setColor(mPlayerOriginalColor);
        }

        if (mPlayerSpriteFlags & IS_MOVING)
        {
            mPlayer->animation->GetAnimationSprite().setScale(mPlayerOriginalScale.x * 2.0f, mPlayerOriginalScale.y * 2.0f);
        }
        else
        {
            mPlayer->animation->GetAnimationSprite().setScale(mPlayerOriginalScale);
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
    if (mGameObjectList.size() != 0)
    {
        for (auto objectIterator = mGameObjectList.begin(); objectIterator != mGameObjectList.end(); objectIterator++)
        {
            auto temp = *objectIterator;
            delete temp;
        }

        auto temp = *mGameObjectList.end();
        delete temp;

        mGameObjectList.clear();

        mPlayer = nullptr;
    }
}