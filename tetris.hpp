#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>

class Tetris {

    static const std::uint32_t LINES {20};
    static const std::uint32_t COLS {10};
    static const std::uint32_t SQUARES {4};
    static const std::uint32_t SHAPES {7};

    std::vector<std::vector<std::uint32_t>> m_area;
    std::vector<std::vector<std::uint32_t>> m_forms;

    struct Coords {
        std::uint32_t x, y;
    } z[SQUARES], k[SQUARES];

    std::unique_ptr<sf::RenderWindow> m_window;
    sf::Texture m_tiles, m_bg;
    std::unique_ptr<sf::Sprite> m_sprite, m_background;
    sf::Clock m_clock;
    sf::Font m_font;
    sf::Text m_txtScore, m_txtGameOver;

    int m_dirx, m_color, m_score;
    bool m_rotate, m_gameover;
    float m_timercount, m_delay;

protected:
    void events();
    void draw();
    void moveToDown();
    void setRotate();
    void resetValues();
    void changePosition();
    bool maxLimit();
    void setScore();

public:
    Tetris();
    void run();
};
