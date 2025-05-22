#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"
#include "SettingsScreen.h"
#include "DifficultyScreen.h"

namespace sfSnake
{
    class GameScreen : public Screen
    {
    public:
        GameScreen(Difficulty difficulty);

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;
        Difficulty getDifficulty();
        Snake getSnake() const;

    private:
        Snake snake_;
        std::vector<Fruit> fruits_;
        sf::Font font_;
        sf::Text scoreText_;

        void initFruits(Difficulty difficulty);
        void updateScore();
        Difficulty difficulty_;

        sf::Color backgroundColor_;
        bool gridEnabled_;
        sf::Color gridColor_;

        void drawGrid(sf::RenderWindow& window);

        float snakeSpeed_;
        bool smallFruits_;
    };
}

#endif
