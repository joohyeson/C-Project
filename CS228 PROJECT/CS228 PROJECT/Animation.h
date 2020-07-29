/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Animation.h
Purpose: This is Animation header file.
Project: CS225
Author: Daeun Jeong
Creation date: 23/07/2020
-----------------------------------------------------------------*/

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
public:
    Animation();
    Animation(sf::Texture& texture, int x, int y, int w, int h, int count, float Speed);
    void Update();
    bool IsAnimationEnded();
    sf::Sprite& GetAnimationSprite();

private:
    sf::Sprite mAnimationSprite;
    std::vector<sf::IntRect> mAnimationCoordinates;
    float mAnimationFrame, mAnimationSpeed;
};