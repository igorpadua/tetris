#include "tetris.hpp"

Tetris::Tetris()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(360, 720), "Tetris", sf::Style::Titlebar | sf::Style::Close);
    window->setPosition(sf::Vector2i(100, 100));

    tiles.loadFromFile("./resources/img/squares.png");
    sprite = std::make_shared<sf::Sprite>();
    sprite->setTexture(tiles);
}

void Tetris::run()
{

}

void Tetris::events()
{
    auto e = std::make_shared<sf::Event>();
    while (window->pollEvent(*e)) {
        if (e->type == sf::Event::Closed) {
            window->close();
        }
    }
}

void Tetris::draw()
{
    window->clear(sf::Color::Black);
    window->draw(*sprite);
    window->display();
}
