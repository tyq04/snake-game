#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Button.h"

namespace sfSnake
{
    class GameOverScreen : public Screen
    {
    public:
        GameOverScreen(unsigned score); // 修改构造函数

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;

    private:
        sf::Font font_;
        sf::Text text_;
        Button menuButton_;
        Button exitButton_;
    };
}

#endif