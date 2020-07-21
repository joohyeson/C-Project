#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "mainmenu.h"
int main()
{
    Engine& engine = Engine::Instance();

    try 
    {
        engine.Init("Week 2");
        MainMenu mainmenu;

        engine.GetGameStateManager().AddGameState(mainmenu);

        while (engine.HasGameEnded() == false) 
        {
            engine.Update();
        }

        engine.Shutdown();
        
        return 0;
    }
    catch (std::exception& e) 
    {
        return -1;
    }
    //sf::RenderWindow window(sf::VideoMode(1280, 720), "MINI GAMES", sf::Style::Close | sf::Style::Resize);

    ////sf::Image image1;
    ////image1.loadFromFile("../Assets/Art/teamLogo.png");
    ////image1.createMaskFromColor(sf::Color(0, 0, 0));

    ////sf::Texture texture1;

    ////if (!texture1.loadFromImage(image1))
    ////{
    ////    // error...
    ////}

    //sf::Font font;
    //font.loadFromFile("../Assets/Font/UhBee Se_hyun.ttf");
    //sf::Text text;

    //text.setFont(font);
    //text.setString("Hello world");
    //text.setPosition(sf::Vector2f(0, 0));
    //text.setCharacterSize(30);
    //text.setStyle(sf::Text::Regular);

    //// sf::Sprite sprite;
    // //sprite.setTexture(texture1);

    //while (window.isOpen())
    //{
    //    sf::Event event;

    //    while (window.pollEvent(event))
    //    {
    //        if (event.type == sf::Event::Closed)
    //            window.close();
    //    }

    //    window.clear();
    //    window.draw(text);
    //    window.display();
    //}

    //return 0;
}