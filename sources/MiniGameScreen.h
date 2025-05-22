#ifndef MINIGAMESCREEN_H
#define MINIGAMESCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"
#include "SettingsScreen.h"

namespace sfSnake
{
    class MiniGameScreen : public Screen
    {
    public:
        MiniGameScreen();

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;

    private:
        Snake snake_;
        std::vector<Fruit> fruits_;
        std::vector<sf::RectangleShape> obstacles_;
        std::vector<sf::RectangleShape> walls_; // 墙壁
        sf::Font font_;
        sf::Text scoreText_;

        void initFruits();
        void initObstacles();
        void initWalls();
        void updateScore();
        void checkObstacleCollisions();
        void checkWallCollisions(); // 检测墙壁碰撞

        sf::Color backgroundColor_;
        bool gridEnabled_;
        sf::Color gridColor_;

        void drawGrid(sf::RenderWindow& window);
    };
}

#endif
