#ifndef DIFFICULTYSCREEN_H
#define DIFFICULTYSCREEN_H

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Button.h"

namespace sfSnake
{
    enum class Difficulty
    {
        Beginner,
        Intermediate,
        Advanced,
        Hell
    };

    class DifficultyScreen : public Screen
    {
    public:
        DifficultyScreen();

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;

    private:
        sf::Font font_;
        sf::Text titleText_;
        Button beginnerButton_;
        Button intermediateButton_;
        Button advancedButton_;
        Button hellButton_;
        Button backButton_;
    };
}

#endif
