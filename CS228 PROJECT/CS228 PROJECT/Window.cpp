/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Window.cpp
Purpose: This is Window source file.
Project: CS225
Author: Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Engine.h" // Engine.GetWindow().Resize()
#include "Window.h"

void Window::Initialize(std::string windowName)
{
    mRenderWindow.create(sf::VideoMode(1280, 720), windowName, sf::Style::Close | sf::Style::Resize);
}

void Window::Resize(int newWidth, int newHeight) 
{
    mRenderWindow.setSize(sf::Vector2u(newWidth, newHeight));
}

sf::Vector2u Window::GetSize() { return mRenderWindow.getSize(); }

sf::RenderWindow& Window::GetWindow(void)
{
    return mRenderWindow;
}

void Window::Clear(sf::Color color)
{
    mRenderWindow.clear(color);
}

void Window::FullScreen()
{
    if (isFullScreen == true)
    {
        mRenderWindow.create(sf::VideoMode(1280, 720), "name", sf::Style::Fullscreen);
    }
    else
    {
        mRenderWindow.create(sf::VideoMode(1280, 720), "name", sf::Style::Close | sf::Style::Resize);
    }
}

void Window::Draw(const sf::Drawable& drawable)
{
    mRenderWindow.draw(drawable);
}

void Window::Update()
{
    mRenderWindow.display();
}

void on_window_resized(int new_width, int new_height) { Engine::GetWindow().Resize(new_width, new_height); }