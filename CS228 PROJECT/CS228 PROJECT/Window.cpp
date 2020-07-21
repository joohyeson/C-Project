/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Window.cpp
Purpose: This is Window source file.
Project: CS280
Author: Juhye Son
Creation date: 21/07/2020
-----------------------------------------------------------------*/

#include "Engine.h" // Engine.GetWindow().Resize()
#include "Window.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

void Window::Initialize(std::string windowName)
{
    mRenderWindow.create(sf::VideoMode(1280, 720), windowName, sf::Style::Close | sf::Style::Resize);
}

void Window::Resize(int newWidth, int newHeight) { mScreenSize.x = newWidth; mScreenSize.y = newHeight; }

Vector2DInt Window::GetSize() { return mScreenSize; }

sf::RenderWindow& Window::GetWindow(void)
{
    return mRenderWindow;
}

void Window::Clear(sf::Color color)
{
    mRenderWindow.clear(color);
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