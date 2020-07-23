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
#include "SFML/Window.hpp"
#include "Animation.h"


const int W = 1200;
const int H = 800;

float DEGTORAD = 0.017453f;

Level2::Level2() {};

void Level2::Load() {}

void Entity::settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1)
{
    anim = a;
    x = X; y = Y;
    angle = Angle;
    R = radius;
}

void Entity::draw(sf::RenderWindow& app)
{
    anim.GetAnimationSprite().setPosition(x, y);
    anim.GetAnimationSprite().setRotation(angle + 90);
    app.draw(anim.GetAnimationSprite());

    sf::CircleShape circle(R);
    circle.setFillColor(sf::Color(255, 0, 0, 170));
    circle.setPosition(x, y);
    circle.setOrigin(R, R);
}

asteroid::asteroid()
{
    dx = rand() % 8 - 4;
    dy = rand() % 8 - 4;
    name = "asteroid";
}

void asteroid::update()
{
    x += dx;
    y += dy;

    if (x > W) x = 0;  if (x < 0) x = W;
    if (y > H) y = 0;  if (y < 0) y = H;
}

bullet::bullet()
{
    name = "bullet";
}

void bullet::update()
{
    dx = cos(angle * DEGTORAD) * 6;
    dy = sin(angle * DEGTORAD) * 6;
    // angle+=rand()%7-3;  /*try this*/
    x += dx;
    y += dy;

    if (x > W || x<0 || y>H || y < 0) life = 0;
}

player::player()
{
    name = "player";
}

void player::update()
{
    if (thrust)
    {
        dx += cos(angle * DEGTORAD) * 0.2;
        dy += sin(angle * DEGTORAD) * 0.2;
    }
    else
    {
        dx *= 0.99;
        dy *= 0.99;
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

bool IsCollide(Entity* a, Entity* b)
{
    return (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y) < (a->R + b->R) * (a->R + b->R);
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

    srand(time(0));

    Engine::GetWindow().GetWindow().setFramerateLimit(60);

    sf::Texture t1, t2, t3, t4, t5, t6, t7;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_blue.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    sf::Sprite background(t2);

    Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
    Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
    Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
    Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
    Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
    Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
    Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);


    std::list<Entity*> entities;

    for (int i = 0; i < 15; i++)
    {
        asteroid* a = new asteroid();
        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
        entities.push_back(a);
    }

    p = new player();

    p->settings(sPlayer, 200, 200, 0, 20);

    entities.push_back(p);

    for (auto a : entities)
    {
        for (auto b : entities)
        {
            if (a->name == "asteroid" && b->name == "bullet")
            {
                if (IsCollide(a, b))
                {
                    a->life = false;
                    b->life = false;

                    Entity* e = new Entity();
                    e->settings(sExplosion, a->x, a->y);
                    e->name = "explosion";
                    entities.push_back(e);


                    for (int i = 0; i < 2; i++)
                    {
                        if (a->R == 15) continue;
                        Entity* e = new asteroid();
                        e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
                        entities.push_back(e);
                    }

                }
            }

            if (a->name == "player" && b->name == "asteroid")
            {
                if (IsCollide(a, b))
                {
                    b->life = false;

                    Entity* e = new Entity();
                    e->settings(sExplosion_ship, a->x, a->y);
                    e->name = "explosion";
                    entities.push_back(e);

                    p->settings(sPlayer, W / 2, H / 2, 0, 20);
                    p->dx = 0; p->dy = 0;
                }
            }
        }
    }


    if (p->thrust)
    {
        p->anim = sPlayer_go;
    }
    else
    {
        p->anim = sPlayer;
    }


    for (auto e : entities)
    {
        if (e->name == "explosion")
        {
            if (e->anim.IsAnimationEnded())
            {
                e->life = 0;
            }
        }
    }

    if (rand() % 150 == 0)
    {
        asteroid* a = new asteroid();
        a->settings(sRock, 0, rand() % H, rand() % 360, 25);
        entities.push_back(a);
    }

    for (auto i = entities.begin(); i != entities.end();)
    {
        Entity* e = *i;

        e->update();
        e->anim.Update();

        if (e->life == false) { i = entities.erase(i); delete e; }
        else i++;
    }

    Engine::GetWindow().Draw(background);

    for (auto i : entities)
    {
        i->draw(Engine::GetWindow().GetWindow());
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
            bullet* b = new bullet();
            b->settings(sBullet, p->x, p->y, p->angle, 10);
            entities.push_back(b);
        }

        if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Right))
        {
            p->angle += 3;
        }
        if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Left))
        {
            p->angle -= 3;
        }
        if (Engine::GetInput().IsKeyPressed(sf::Keyboard::Up))
        {
            p->thrust = true;
        }
        else
        {
            p->thrust = false;
        }
    }

    if (Engine::GetInput().IsKeyPressed(sf::Keyboard::R))
    {
        Engine::GetGameStateManager().ReloadState();
        mShouldGameRun = true;
    }
}

void Level2::Unload() {}