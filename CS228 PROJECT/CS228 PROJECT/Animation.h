/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Animation.h
Purpose: This is Animation header file.
Project: CS225
Author: Daeun Jeong, Juhye Son
Creation date: 23/07/2020
-----------------------------------------------------------------*/

#pragma once
#include <SFML/Graphics.hpp>
#include <vector> //std::vector

class GameObject;

class Animation
{
public:
    Animation() = default;
    Animation(sf::Texture& texture, int x, int y, int w, int h, int count, float speed);
    void Update();
    bool IsAnimationEnded();
    sf::Sprite& GetAnimationSprite();
    void SetSpriteColor(sf::Color color);
    void SetSpriteScale(sf::Vector2f scale);
    void SetOwner(GameObject* owner);

private:
    GameObject* mOwner = nullptr;

    sf::Sprite mAnimationSprite;
    std::vector<sf::IntRect> mAnimationCoordinates;
    float mAnimationFrame, mAnimationSpeed;

    bool mIsAnimationEnded = true;
};