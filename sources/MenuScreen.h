#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Button.h"

namespace sfSnake
{
    class MenuScreen : public Screen
    {
    public:
        MenuScreen();

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;

    private:
        sf::Font font_;
        sf::Text titleText_;
        Button playButton_;
        Button settingsButton_;
        Button helpButton_;
        Button miniGameButton_;
        Button backButton_;
        sf::Texture titleTexture_;
        sf::Sprite titleSprite_;
    };
}

#endif
