#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>

class Tetris
{
public:
    Tetris();
    void run();

protected:
    void events();
    void draw();
    void moveToDown();
    void setRotate();
    void resetValues();
    void changePosition();
    bool maxLimit();

private:
    std::unique_ptr<sf::RenderWindow> m_window;
    std::unique_ptr<sf::Sprite> m_sprite;
    sf::Texture m_tiles;
    sf::Clock clock;

    int m_dirx, m_color;
    bool m_rotate;
    float m_timerCount, delay;

    static const std::uint32_t LINES = 20;
    static const std::uint32_t COLS = 10;
    static const std::uint32_t SQUARES = 4;
    static const std::uint32_t SHAPES = 7;

    std::vector<std::vector<std::uint32_t>> m_area;
    std::vector<std::vector<std::uint32_t>> m_forms;

    struct Coords
    {
        std::uint32_t x, y;
    } z[SQUARES], k[SQUARES];

    void closedWindow(const sf::Event& e);
    void rotate(const sf::Event& e);
};

