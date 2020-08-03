/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Animation.cpp
Purpose: This is Animation source file.
Project: CS225
Author: Daeun Jeong
Creation date: 23/07/2020
-----------------------------------------------------------------*/

#include "Animation.h"
#include "Colors.h"

void Animation::SetAnimationValues(sf::Texture texture, int x, int y, int w, int h, int count, float speed)
{
    mAnimationFrame = 0;
    mAnimationSpeed = speed;

    for (int i = 0; i < count; ++i)
    {
        mAnimationCoordinates.push_back(sf::IntRect(x + i * w, y, w, h));
    }

    mAnimationSprite.setTexture(texture);
    mAnimationSprite.setOrigin(w / 2.0f, h / 2.0f);
    mAnimationSprite.setTextureRect(mAnimationCoordinates[0]);
}

Animation::Animation(eTexture textureEnum)
{
    sf::Texture texture;
    
    switch (textureEnum)
    {
    case eTexture::BULLET:
        texture.loadFromFile("../Assets/Art/fire_blue.png");
        SetAnimationValues(texture, 0, 0, 32, 64, 16, 0.8f);
        break;
    case eTexture::PLAYER:
        texture.loadFromFile("../Assets/Art/spaceship.png");
        texture.setSmooth(true);
        SetAnimationValues(texture, 40, 0, 40, 40, 1, 0.f);
        break;
    case eTexture::PLAYER_MOVE:
        texture.loadFromFile("../Assets/Art/spaceship.png");
        texture.setSmooth(true);
        SetAnimationValues(texture, 40, 40, 40, 40, 1, 0.f);
        break;
    case eTexture::EXPLOSION:
        texture.loadFromFile("../Assets/Art/explosions/type_C.png");
        SetAnimationValues(texture, 0, 0, 256, 256, 48, 0.5f);
        break;
    case eTexture::ROCK:
        texture.loadFromFile("../Assets/Art/rock.png");
        SetAnimationValues(texture, 0, 0, 64, 64, 16, 0.2f);
        break;
    case eTexture::SMALL_ROCK:
        texture.loadFromFile("../Assets/Art/rock_small.png");
        SetAnimationValues(texture, 0, 0, 64, 64, 16, 0.2f);
        break;
    default:
        break;
    }
}

void Animation::Update()
{
    mAnimationFrame += mAnimationSpeed;

    int frameSize = static_cast<int>(mAnimationCoordinates.size());

    if (mAnimationFrame >= frameSize)
    {
        mAnimationFrame -= frameSize;
    }

    if (frameSize > 0)
    {
        mAnimationSprite.setTextureRect(mAnimationCoordinates[static_cast<int>(mAnimationFrame)]);
    }
}

bool Animation::IsAnimationEnded()
{
    return mAnimationFrame + mAnimationSpeed >= mAnimationCoordinates.size();
}

sf::Sprite& Animation::GetAnimationSprite()
{
    return mAnimationSprite;
}
