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
    void moveToDow();

private:
    std::shared_ptr<sf::RenderWindow> window;
    sf::Texture tiles;
    std::shared_ptr<sf::Sprite> sprite;

    static const std::uint32_t lines {20};
    static const std::uint32_t cols {10};
    static const std::uint32_t squares {4};
    static const std::uint32_t shapes {7};

    struct Coords
    {
        std::uint32_t x, y;
    }z[squares], k[squares];

    std::vector<std::vector<std::uint32_t>> area;
    std::vector<std::vector<std::uint32_t>> forms;
};

