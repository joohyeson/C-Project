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

enum class eLevel2Texture
{
    NONE,
    BULLET,
    PLAYER,
    PLAYER_MOVE,
    EXPLOSION,
    ROCK,
    SMALL_ROCK
};

class Level2 : public GameState
{
public:
    Level2() = default;
    ~Level2();

    Level2(const Level2& rhs);
    Level2(Level2&& rhs);
    Level2& operator=(const Level2& rhs);
    Level2& operator=(Level2&& rhs);

    Animation LoadAnimation(eLevel2Texture textureEnum);
    void Load() override;
    void Update(double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override { return "Level2"; }

private:
    bool mIsGameOver;
    bool mIsGameCleared;

    unsigned char mPlayerSpriteFlags;

    int mBulletLimit;

    float mBulletTimer;
    float mPlayerMoveTimer;

    Player* mPlayer;
    sf::Vector2f mPlayerOriginalScale;
    sf::Color mPlayerOriginalColor;
    List<GameObject*> mGameObjectList;

    sf::Texture bulletTexture;
    sf::Texture playerTexture;
    sf::Texture playerMoveTexture;
    sf::Texture explosionTexture;
    sf::Texture rockTexture;
    sf::Texture smallRockTexture;
    sf::Texture backgroundTexture;

    sf::Sprite backgroundSprite;

    Animation bulletAnimation;
    Animation playerAnimation;
    Animation playerMoveAnimation;
    Animation explosionAnimation;
    Animation rockAnimation;
    Animation smallRockAnimation;

    void DeepCopy(const Level2& rhs);
};