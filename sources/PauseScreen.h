#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include <memory>
#include "button.h"

namespace sfSnake
{
    class GameScreen;

    class PauseScreen : public Screen
    {
    public:
        PauseScreen(std::shared_ptr<GameScreen> gameScreen);

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;

    private:
        sf::Font font_;
        sf::Text text_;
        std::shared_ptr<GameScreen> gameScreen_;
        Button restartButton;
        Button continueButton;
        Button MenuButton;
    };
}

#endif
