#include "tetris.hpp"

Tetris::Tetris() :
    m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(360, 720), "Tetris", sf::Style::Titlebar | sf::Style::Close))
  , m_sprite(std::make_unique<sf::Sprite>())
{
    m_window->setPosition(sf::Vector2i(100, 100));

    m_tiles.loadFromFile("./resources/img/squares.png");
    m_sprite->setTexture(m_tiles);
}

void Tetris::run()
{
    while (m_window->isOpen()) {
        events();
        draw();
    }
}

void Tetris::events()
{
    closedWindow();
}

void Tetris::draw()
{
    m_window->clear(sf::Color::Black);
    m_window->draw(*m_sprite);
    m_window->display();
}

void Tetris::closedWindow()
{
    auto e = std::make_unique<sf::Event>();

    while (m_window->pollEvent(*e)) {
        if (e->type == sf::Event::Closed) {
            m_window->close();
        }
    }
}
