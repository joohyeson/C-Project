
#include "Engine.h"			// Engine.GetWindow()
#include "Window.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

sf::RenderWindow window;
void Window::Init(std::string windowName) {
    window.create(sf::VideoMode(1280, 720), windowName, sf::Style::Close | sf::Style::Resize);

	/*doodle::create_window(windowName, 1140, 810);
	doodle::set_frame_of_reference(doodle::FrameOfReference::RightHanded_OriginBottomLeft);
	doodle::set_image_mode(doodle::RectMode::Corner);*/
}

void Window::Resize(int newWidth, int newHeight) { screenSize.x = newWidth; screenSize.y = newHeight; }

Vector2DInt Window::GetSize() { return screenSize; }

void Window::Clear(sf::Color color) { 
   window.clear(color);
}
void Window::Draw(const sf::Drawable& drawable)
{
    window.draw(drawable);
}
void Window::Update() { 
    window.display();
}

void on_window_resized(int new_width, int new_height) { Engine::GetWindow().Resize(new_width, new_height); }