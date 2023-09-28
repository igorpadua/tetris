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

private:
    std::shared_ptr<sf::RenderWindow> window;
    sf::Texture tiles;
    std::shared_ptr<sf::Sprite> sprite;
};

