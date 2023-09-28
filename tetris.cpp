#include "tetris.hpp"
#include <iostream>

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
        moveToDown();
        draw();
    }
}

void Tetris::events()
{
    auto e = std::make_shared<sf::Event>();
    while (m_window->pollEvent(*e)) {
        if (e->type == sf::Event::Closed) {
            m_window->close();
        }
    }
    closedWindow();
}

void Tetris::draw()
{
    m_window->clear(sf::Color::Black);
    for (int i = 0; i < SQUARES; ++i) {
        m_sprite->setPosition(z[i].x * 36, z[i].y * 36);
        m_window->draw(*m_sprite);
    }
    m_window->display();
}

void Tetris::moveToDown()
{
    auto number = std::uint32_t(3);
    if (z[0].x != 0) {
        for (std::size_t i = {}; i < SQUARES; ++i) {
            z[i].x = m_forms[number][i] % 2;
            z[i].y = m_forms[number][i] / 2;
        }
    }
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
