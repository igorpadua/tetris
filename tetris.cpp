#include "tetris.hpp"
#include <iostream>

Tetris::Tetris()
{
    area.resize(lines);

    for (int i = 0; i < area.size(); ++i) {
        area[i].resize(cols);
    }

    z[0].x = 0;

    forms = {
        {1, 3, 5, 7},
        {2, 4, 5, 7},
        {3, 5, 4, 6},
        {3, 5, 4, 7},
        {2, 3, 5, 7},
        {3, 5, 7, 6},
        {2, 3, 4, 5}
    };

    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(360, 720), "Tetris", sf::Style::Titlebar | sf::Style::Close);
    window->setPosition(sf::Vector2i(100, 100));

    tiles.loadFromFile("./resources/img/squares.png");
    sprite = std::make_shared<sf::Sprite>();
    sprite->setTexture(tiles);
    sprite->setTextureRect(sf::IntRect(0, 0, 36, 36));
}

void Tetris::run()
{
    while (window->isOpen()) {
        events();
        moveToDow();
        draw();
    }
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
    for (int i = 0; i < squares; ++i) {
        sprite->setPosition(z[i].x * 36, z[i].y * 36);
        window->draw(*sprite);
    }
    window->display();
}

void Tetris::moveToDow()
{
    std::uint32_t number = 3;

    if (z[0].x == 0) {
        std::cout << "entrou" << std::endl;
        for (int i = 0; i < squares; ++i) {
            z[i].x = forms[number][i] & 2;
            z[i].y = forms[number][i] / 2;
        }
    }
}
