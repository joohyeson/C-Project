#pragma once
#include "BasicDataTypes.h"
#include <SFML\Graphics\Color.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

class Window
{
public:
    void Init(std::string windowName);
    void Update();
    void Resize(int newWidth, int newHeight);
    Vector2DInt GetSize();
    void Draw(const sf::Drawable& drawable);
    void Clear(sf::Color color);

private:
    Vector2DInt screenSize;
};