/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Animation.cpp
Purpose: This is Animation source file.
Project: CS225
Author: Daeun Jeong, Juhye Son
Creation date: 23/07/2020
-----------------------------------------------------------------*/

#include "Animation.h"
#include "Colors.h"

Animation::Animation(sf::Texture& texture, int x, int y, int w, int h, int count, float speed)
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

void Animation::Update()
{
    int frameSize = static_cast<int>(mAnimationCoordinates.size());
    
    if (mAnimationFrame >= mAnimationCoordinates.size())
    {
        mAnimationFrame -= frameSize;
    }

    if (frameSize > 0)
    {
        mAnimationSprite.setTextureRect(mAnimationCoordinates[static_cast<int>(mAnimationFrame)]);
    }

    mAnimationFrame += mAnimationSpeed;
}

bool Animation::IsAnimationEnded()
{
    return mAnimationFrame + mAnimationSpeed >= mAnimationCoordinates.size();
}

sf::Sprite& Animation::GetAnimationSprite()
{
    return mAnimationSprite;
}