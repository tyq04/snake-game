#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Button.h"

namespace sfSnake
{
    class SettingsScreen : public Screen
    {
    public:
        SettingsScreen();

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;

        sf::Color getBackgroundColor() const;
        bool isGridEnabled() const;
        sf::Color getGridColor() const;

    private:
        sf::Font font_;
        sf::Text titleText_;
        sf::Color backgroundColor_;
        bool gridEnabled_;
        sf::Color gridColor_;

        Button blackBgButton_;
        Button whiteBgButton_;
        Button brownBgButton_;
        Button toggleGridButton_;
        Button blackGridButton_;
        Button whiteGridButton_;
        Button brownGridButton_;
        Button backButton_;
    };
}

#endif
