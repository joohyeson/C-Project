/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.cpp
Purpose: This is Level1 source file.
Project: CS280
Author: Daeun Jeong, Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "Level2.h"
#include "Engine.h" //Engine::GetWindow()
#include "Window.h"

const int W = 1280;
const int H = 720;

float DEGREE_TO_RADIAN = 0.017453f;

Level2::Level2() {};

void Level2::Load() {}

void GameObject::SetValues(Animation& newAnimation, float newX, float newY, float newAngle, float newRadius)
{
    animation = newAnimation;
    x = newX;
    y = newY;
    angle = newAngle;
    radius = newRadius;
}

void GameObject::Draw(sf::RenderWindow& window)
{
    animation.GetAnimationSprite().setPosition(x, y);
    animation.GetAnimationSprite().setRotation(angle + 90);
    window.draw(animation.GetAnimationSprite());

    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(255, 0, 0, 170));
    circle.setPosition(x, y);
    circle.setOrigin(radius, radius);
}

Asteroid::Asteroid()
{
    dx = rand() % 8 - 4.0f;
    dy = rand() % 8 - 4.0f;
    name = "asteroid";
}

void Asteroid::Update()
{
    x += dx;
    y += dy;

    if (x > W)
    {
        x = 0;
    }

    if (x < 0)
    {
        x = W;
    }

    if (y > H)
    {
        y = 0;
    }

    if (y < 0)
    {
        y = H;
    }
}

Bullet::Bullet()
{
    name = "bullet";
}

void Bullet::Update()
{
    dx = cos(angle * DEGREE_TO_RADIAN) * 6;
    dy = sin(angle * DEGREE_TO_RADIAN) * 6;
    // angle+=rand()%7-3;  /*try this*/
    x += dx;
    y += dy;

    if (x > W || x<0 || y>H || y < 0)
    {
        isAlive = 0;
    }
}

Player::Player()
{
    name = "player";
}

void Player::Update()
{
    if (isMoving)
    {
        dx += cos(angle * DEGREE_TO_RADIAN) * 0.2f;
        dy += sin(angle * DEGREE_TO_RADIAN) * 0.2f;
    }
    else
    {
        dx *= 0.99f;
        dy *= 0.99f;
    }

    int maxSpeed = 15;

    float speed = sqrt(dx * dx + dy * dy);

    if (speed > maxSpeed)
    {
        dx *= maxSpeed / speed;
        dy *= maxSpeed / speed;
    }

    x += dx;
    y += dy;

    if (x > W) x = 0; if (x < 0) x = W;
    if (y > H) y = 0; if (y < 0) y = H;
}

bool GameObject::IsCollide(GameObject* a, GameObject* b)
{
    return (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y) < (a->radius + b->radius) * (a->radius + b->radius);
}

void Level2::Draw()
{
    Engine::GetWindow().Clear(sf::Color(51, 153, 218, 255));

    sf::Font font;
    font.loadFromFile("../Assets/Font/UhBee Se_hyun.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString("Asteroid");
    text.setPosition(sf::Vector2f(0, 0));
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Regular);
    Engine::GetWindow().Draw(text);

    srand(static_cast<unsigned int>(time(0)));

    Engine::GetWindow().GetWindow().setFramerateLimit(60);

    sf::Texture shipTexture, backgroundTexture, explosionTexture, rockTexture, bulletTexture, smallRockTexture, explosionShipTexture;

    shipTexture.loadFromFile("../Assets/Art/spaceship.png");
    backgroundTexture.loadFromFile("../Assets/Art/background.jpg");
    explosionTexture.loadFromFile("../Assets/Art/explosions/type_C.png");
    rockTexture.loadFromFile("../Assets/Art/rock.png");
    bulletTexture.loadFromFile("../Assets/Art/fire_blue.png");
    smallRockTexture.loadFromFile("../Assets/Art/rock_small.png");
    explosionShipTexture.loadFromFile("../Assets/Art/explosions/type_B.png");

    shipTexture.setSmooth(true);
    backgroundTexture.setSmooth(true);

    sf::Sprite backgroundSprite(backgroundTexture);

    Animation explosionAnimation(explosionTexture, W / 2, H / 2, 256, 256, 48, 0.5f);
    Animation rockAnimation(rockTexture, W / 2, H / 2, 64, 64, 16, 0.2f);
    Animation smallRockAnimation(smallRockTexture, W / 2, H / 2, 64, 64, 16, 0.2f);
    mBulletAnimation = Animation(bulletTexture, W / 2, H / 2, 32, 64, 16, 0.8f);
    Animation playerAnimation(shipTexture, 40, W / 2, 40, 40, 1, 0.0f);
    Animation playerMoveAnimation(shipTexture, 40, 40, 40, 40, 1, 0.0f);
    Animation explosionShipAnimation(explosionShipTexture, W / 2, H / 2, 192, 192, 64, 0.5f);

    for (int i = 0; i < 15; i++)
    {
        Asteroid* asteroid = new Asteroid();
        asteroid->SetValues(rockAnimation, static_cast<float>(rand() % W), static_cast<float>(rand() % H), static_cast<float>(rand() % 360), 25.0f);
        mEntityList.push_back(asteroid);
    }

    mPlayer = new Player();

    mPlayer->SetValues(playerAnimation, 200, 200, 0, 20);

    mEntityList.push_back(mPlayer);

    for (auto entityA : mEntityList)
    {
        for (auto entityB : mEntityList)
        {
            if (entityA->name == "asteroid" && entityB->name == "bullet")
            {
                if (IsCollide(entityA, entityB))
                {
                    entityA->isAlive = false;
                    entityB->isAlive = false;

                    GameObject* explosion = new GameObject();
                    explosion->SetValues(explosionAnimation, entityA->x, entityA->y);
                    explosion->name = "explosion";
                    mEntityList.push_back(explosion);

                    for (int i = 0; i < 2; i++)
                    {
                        if (entityA->radius == 15)
                        {
                            continue;
                        }

                        GameObject* entity = new Asteroid();
                        entity->SetValues(smallRockAnimation, entityA->x, entityA->y, static_cast<float>(rand() % 360), 15.0f);
                        mEntityList.push_back(entity);
                    }
                }
            }

            if (entityA->name == "player" && entityB->name == "asteroid")
            {
                if (IsCollide(entityA, entityB))
                {
                    entityB->isAlive = false;

                    GameObject* e = new GameObject();
                    e->SetValues(explosionShipAnimation, entityA->x, entityA->y);
                    e->name = "explosion";
                    mEntityList.push_back(e);

                    mPlayer->SetValues(playerAnimation, W / 2, H / 2, 0, 20);
                    mPlayer->dx = 0;
                    mPlayer->dy = 0;
                }
            }
        }
    }

    if (mPlayer->isMoving)
    {
        mPlayer->animation = playerMoveAnimation;
    }
    else
    {
        mPlayer->animation = playerAnimation;
    }

    for (auto explosion : mEntityList)
    {
        if (explosion->name == "explosion")
        {
            if (explosion->animation.IsAnimationEnded())
            {
                explosion->isAlive = 0;
            }
        }
    }

    if (rand() % 150 == 0)
    {
        Asteroid* asteroid = new Asteroid();
        asteroid->SetValues(rockAnimation, 0.0f, static_cast<float>(rand() % H), static_cast<float>(rand() % 360), 25.0f);
        mEntityList.push_back(asteroid);
    }

    for (auto entityIterator = mEntityList.begin(); entityIterator != mEntityList.end();)
    {
        GameObject* entity = *entityIterator;

        entity->Update();
        entity->animation.Update();

        if (entity->isAlive == false)
        {
            entityIterator = mEntityList.erase(entityIterator);
            delete entity;
        }
        else
        {
            entityIterator++;
        }
    }

    Engine::GetWindow().Draw(backgroundSprite);

    for (auto entity : mEntityList)
    {
        entity->Draw(Engine::GetWindow().GetWindow());
    }

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
        if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Space))
        {
            Bullet* bullet = new Bullet();
            bullet->SetValues(mBulletAnimation, mPlayer->x, mPlayer->y, mPlayer->angle, 10.0f);
            mEntityList.push_back(bullet);
        }

        if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Right))
        {
            mPlayer->angle += 3;
        }

        if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Left))
        {
            mPlayer->angle -= 3;
        }

        if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Up))
        {
            mPlayer->isMoving = true;
        }
        else
        {
            mPlayer->isMoving = false;
        }
    }

    if (Engine::GetInput().IsKeyPressed(sf::Keyboard::R))
    {
        Engine::GetGameStateManager().ReloadState();
        mShouldGameRun = true;
    }
}

void Level2::Unload() {}