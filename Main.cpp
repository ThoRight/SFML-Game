#include <SFML/Graphics.hpp>
#include "Scene.h"

int main()
{
    //srand(time(NULL));
    Game game(1280,1024);
    game.run();
    
/*
    sf::RenderWindow window(sf::VideoMode(557, 500), "My window");

    sf::Texture texture;
    if (!texture.loadFromFile("./Assets/player.png"))
    {
        exit(1);
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 150, 368 / 8, 50));
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
*/
    return 0;
}