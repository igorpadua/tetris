#include "tetris.hpp"
#include <iostream>

Tetris::Tetris() :
    m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(360, 720), "Tetris", sf::Style::Titlebar | sf::Style::Close))
  , m_sprite(std::make_unique<sf::Sprite>())
  , m_forms({{1,3,5,7},{2,4,5,7},{3,5,4,6},{3,5,4,7},{2,3,5,7},{3,5,7,6},{2,3,4,5}})
  , m_dirx(0)
  , m_rotate(false)
  , m_timerCount(0)
  , delay(0.3f)
  , m_color(1)
{
    m_area.resize(LINES);

    for (auto& area : m_area) {
        area.resize(COLS);
    }

    m_window->setPosition(sf::Vector2i(100, 100));

    m_tiles.loadFromFile("./resources/img/squares.png");
    m_sprite->setTexture(m_tiles);
    m_sprite->setTextureRect(sf::IntRect(0, 0, 36, 36));

    auto number = std::rand() % SHAPES;
    for (std::size_t i = {}; i < SQUARES; ++i) {
        z[i].x = m_forms[number][i] % 2;
        z[i].y = m_forms[number][i] / 2;
    }
}

void Tetris::run()
{
    while (m_window->isOpen()) {
        events();
        changePosition();
        setRotate();
        moveToDown();
        resetValues();
        draw();
    }
}

void Tetris::events()
{
    auto time = clock.getElapsedTime().asSeconds();
    clock.restart();
    m_timerCount += time;

    auto e = std::make_unique<sf::Event>();

    while (m_window->pollEvent(*e)) {
        closedWindow(*e);
        rotate(*e);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        delay = 0.05f;
    }
}

void Tetris::draw()
{
    m_window->clear(sf::Color::Black);

    for (int i = 0; i < LINES; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (m_area[i][j] != 0) {
                m_sprite->setPosition(j * 36, i * 36);
                m_window->draw(*m_sprite);
            }
        }
    }

    m_window->display();
}

void Tetris::moveToDown()
{
    if (m_timerCount > delay) {
        for (int i = 0; i < SHAPES; ++i) {
            k[i] = z[i];
            ++z[i].y;
        }
    }

    if (maxLimit()) {

        for (int i = 0; i < SQUARES; ++i) {
            m_area[k[i].y][k[i].x] = m_color;
        }

        m_color = std::rand() % SHAPES + 1;
        auto number = std::rand() % SHAPES;
        for (std::size_t i = {}; i < SQUARES; ++i) {
            z[i].x = m_forms[number][i] % 2;
            z[i].y = m_forms[number][i] / 2;
        }
    }


    m_timerCount = 0;
}

void Tetris::setRotate()
{
    if (m_rotate) {
        auto coords = z[1];
        for (int i = 0; i < SQUARES; ++i) {
            auto x = z[i].y - coords.y;
            auto y = z[i].x + coords.x;

            z[i].x = coords.x - x;
            z[i].y = coords.y + y;
        }

        if (maxLimit()) {
            for (int i = 0; i < SQUARES; ++i) {
                z[i] = k[i];
            }
        }
    }
}

void Tetris::resetValues()
{
    m_dirx = 0;
    m_rotate = false;
    delay = 0.3f;
}

void Tetris::changePosition()
{
    for (int i = 0; i < SQUARES; ++i) {
        k[i] = z[i];
        z[i].x += m_dirx;
    }

    if (maxLimit()) {
        for (int i = 0; i < SQUARES; ++i) {
            z[i] = k[i];
        }
    }
}

bool Tetris::maxLimit()
{
    for (int i = 0; i < SQUARES; ++i) {
        if (z[i].x < 0 or z[i].x >= COLS or z[i].y >= LINES or m_area[z[i].y][z[i].x]) {
            return true;
        }
    }
    return false;
}

void Tetris::closedWindow(const sf::Event& e)
{
    if (e.type == sf::Event::Closed) {
        m_window->close();
    }
}

void Tetris::rotate(const sf::Event& e)
{
   if (e.type == sf::Event::KeyPressed) {
       if (e.key.code == sf::Keyboard::Up) {
           m_rotate = true;
       } else if (e.key.code == sf::Keyboard::Right) {
           ++m_dirx;
       } else if (e.key.code == sf::Keyboard::Left) {
           --m_dirx;
       }
   }
}
