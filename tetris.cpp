#include "tetris.hpp"

Tetris::Tetris() :
    m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(360, 720), "Tetris", sf::Style::Titlebar | sf::Style::Close))
  , m_sprite(std::make_unique<sf::Sprite>())
  , m_forms({{1,3,5,7},{2,4,5,7},{3,5,4,6},{3,5,4,7},{2,3,5,7},{3,5,7,6},{2,3,4,5}})
{
    m_area.resize(LINES);

    for (auto area : m_area) {
        area.resize(COLS);
    }

    m_window->setPosition(sf::Vector2i(100, 100));

    m_tiles.loadFromFile("./resources/img/squares.png");
    m_sprite->setTexture(m_tiles);
    m_sprite->setTextureRect(sf::IntRect(0, 0, 36, 36));
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
