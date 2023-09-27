#include "tetris.hpp"

int main(int argc, char** argv)
{
    auto tetris = std::make_unique<Tetris>();
    tetris->run();

    return 0;
}
