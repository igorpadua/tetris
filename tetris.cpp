#include "tetris.hpp"

Tetris::Tetris() :
    m_window(std::make_unique<sf::RenderWindow>(
                 sf::VideoMode(360, 720),
                 "Tetris (remix)",
                 sf::Style::Titlebar | sf::Style::Close))
  , m_sprite(std::make_unique<sf::Sprite>())
  , m_forms({{1,3,5,7}, {2,4,5,7}, {3,5,4,6}, {3,5,4,7}, {2,3,5,7}, {3,5,7,6}, {2,3,4,5}})
  , m_background(std::make_unique<sf::Sprite>())
  , m_dirx(0)
  , m_score(0)
  , m_rotate(false)
  , m_gameover(false)
  , m_timercount(0.f)
  , m_delay(0.3f)
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

    m_bg.loadFromFile("./resources/img/background.png");
    m_background->setTexture(m_bg);


    auto number = std::rand() % SHAPES;
    for (std::size_t i {}; i < SQUARES; ++i) {
        z[i].x = m_forms[number][i] % 2;
        z[i].y = m_forms[number][i] / 2;
    }

    m_font.loadFromFile("./resources/font/font.ttf");
    m_txtScore.setFont(m_font);
    m_txtScore.setPosition(100.f,10.f);
    m_txtScore.setString("SCORE: " + std::to_string(m_score));
    m_txtScore.setCharacterSize(30);
    m_txtScore.setOutlineThickness(3);

    m_txtGameOver.setFont(m_font);
    m_txtGameOver.setPosition(30.f,300.f);
    m_txtGameOver.setString("GAME OVER");
    m_txtGameOver.setCharacterSize(50);
    m_txtGameOver.setOutlineThickness(3);
}

void Tetris::events()
{

    auto time = m_clock.getElapsedTime().asSeconds();
    m_clock.restart();
    m_timercount += time;

    auto e = std::make_shared<sf::Event>();
    while(m_window->pollEvent(*e)){
        if(e->type == sf::Event::Closed){
            m_window->close();
        }

        if(e->type == sf::Event::KeyPressed){
            if(e->key.code == sf::Keyboard::Up){
                m_rotate = true;
            }else if(e->key.code == sf::Keyboard::Right){
                ++m_dirx;
            }else if(e->key.code == sf::Keyboard::Left){
                --m_dirx;
            }
        }
    }

    if( sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        m_delay = 0.05f;
    }
}

void Tetris::draw(){
    m_window->clear(sf::Color::Black);
    m_window->draw(*m_background);

    for (std::size_t i {}; i < LINES; ++i) {
        for (std::size_t j {}; j < COLS; ++j) {
            if(m_area[i][j] != 0){
                m_sprite->setTextureRect(sf::IntRect(m_area[i][j] * 36, 0, 36, 36));
                m_sprite->setPosition(j * 36, i * 36);
                m_window->draw(*m_sprite);

            }
        }
    }

    for (std::size_t i {}; i < SQUARES; ++i) {
        m_sprite->setTextureRect(sf::IntRect(m_color * 36, 0, 36, 36));
        m_sprite->setPosition( z[i].x * 36, z[i].y * 36);
        m_window->draw(*m_sprite);
    }

    m_window->draw(m_txtScore);
    if(m_gameover){
        m_window->draw(m_txtGameOver);
    }
    m_window->display();
}


void Tetris::run(){
    while(m_window->isOpen()){
        events();
        if(!m_gameover){
            changePosition();
            setRotate();
            moveToDown();
            setScore();
            resetValues();
        }
        draw();
    }
}

void Tetris::moveToDown(){
    if(m_timercount > m_delay){
        for (std::size_t i {}; i < SQUARES; ++i) {
            k[i] = z[i];
            ++z[i].y;
        }

        if(maxLimit()){

            for (std::size_t i {}; i < SQUARES; ++i) {
                m_area[ k[i].y ][ k[i].x ] = m_color;
            }

            m_color = std::rand() % SHAPES + 1;
            std::uint32_t number = std::rand() % SHAPES;
            for (std::size_t i {}; i < SQUARES; ++i) {
                z[i].x = m_forms[number][i] % 2;
                z[i].y = m_forms[number][i] / 2;
            }
        }

        m_timercount = 0;
    }

}

void Tetris::setRotate(){
    if(m_rotate){
        Coords coords = z[1];
        for (std::size_t i {}; i < SQUARES; ++i) {
            int x = z[i].y - coords.y;
            int y = z[i].x - coords.x;

            z[i].x = coords.x - x;
            z[i].y = coords.y + y;
        }

        if(maxLimit()){
            for (std::size_t i {}; i < SQUARES; ++i) {
                z[i] = k[i];
            }
        }
    }
}

void Tetris::resetValues(){
    m_dirx = 0;
    m_rotate = false;
    m_delay = 0.3f;
}

void Tetris::changePosition(){
    for (std::size_t i {}; i < SQUARES; ++i) {
        k[i] = z[i];
        z[i].x += m_dirx;
    }

    if( maxLimit() ){
        for (std::size_t i {}; i < SQUARES; ++i) {
            z[i] = k[i];
        }
    }
}

bool Tetris::maxLimit(){
    for (std::size_t i {}; i < SQUARES; ++i) {
        if( z[i].x < 0 or
                z[i].x >= COLS or
                z[i].y >= LINES or
                m_area[ z[i].y ][ z[i].x ]){
            return true;
        }
    }
    return false;
}

void Tetris::setScore(){
    std::uint32_t match = LINES - 1;
    for (std::size_t i = match; i >= 1; --i) {
        std::uint32_t sum {};
        for (std::size_t j {}; j < COLS; ++j) {
            if(m_area[i][j]){
                if( i == 1 ){
                    m_gameover = true;
                }
                ++sum;
            }
            m_area[match][j] = m_area[i][j];
        }
        if(sum < COLS){
            --match;
        }else{
            m_txtScore.setString("SCORE: " + std::to_string(++m_score));
        }
    }
}
