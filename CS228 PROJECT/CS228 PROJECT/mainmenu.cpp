#include "mainmenu.h"
#include "Engine.h"
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

MainMenu::MainMenu(){};

void MainMenu::Load()
{

}
void MainMenu::Draw()
{
	//Engine::GetWindow().Clear(sf::Color(51, 153, 218, 255));
}
void MainMenu::Update(double/* dt*/)
{
	sf::Font font;
	font.loadFromFile("../Assets/Font/UhBee Se_hyun.ttf");
	sf::Text text;

	text.setFont(font);
	text.setString("Hello world");
	text.setPosition(sf::Vector2f(0, 0));
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Regular);

	// sf::Sprite sprite;
	 //sprite.setTexture(texture1);

	Engine::GetWindow().Clear(sf::Color(51, 153, 218, 255));
	Engine::GetWindow().Draw(text);
	Engine::GetWindow().Update();
	
}
void MainMenu::Unload()
{
}