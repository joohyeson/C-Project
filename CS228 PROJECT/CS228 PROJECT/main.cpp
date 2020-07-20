#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Hello World!", sf::Style::Close | sf::Style::Resize);

    sf::Image image1;
    image1.loadFromFile("../Assets/Art/teamLogo.png");
    image1.createMaskFromColor(sf::Color(0, 0, 0));

    sf::Texture texture1;

    if (!texture1.loadFromImage(image1))
    {
        // error...
    }

    sf::Sprite sprite;
    sprite.setTexture(texture1);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}