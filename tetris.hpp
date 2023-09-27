#pragma once

#include <SFML/Graphics.hpp>
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
    std::unique_ptr<sf::RenderWindow> m_window;
    std::unique_ptr<sf::Sprite> m_sprite;
    sf::Texture m_tiles;

    void closedWindow();
};

