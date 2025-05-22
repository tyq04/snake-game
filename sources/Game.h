// Game.h
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Screen.h"
#include <cmath>
#include <SFML/Audio.hpp>

namespace sfSnake
{
    class Game
    {
    private:
        
    public:
        static const int Width = 800;
        static const int Height = 600;
        static std::shared_ptr<Screen> Screen;
        static sf::VideoMode initVideoMode_();

        static sf::VideoMode GlobalVideoMode;
        static sf::Music backgroundMusic_;

        class Color
        {
        public:
            static const sf::Color Yellow;
            static const sf::Color Green;
            static const sf::Color Background[3];
            static const sf::Color Grid[3];
            static const sf::Color NotSeleted;
            static const sf::Color Fruit[5];
        };

        static void playbackgroundmusic(const std::string& filename);
        static void start();
        
    };
}

template <typename T>
    inline sf::FloatRect setOriginMiddle(T &shape)
    {
        sf::FloatRect shapeBounds = shape.getLocalBounds();
        shape.setOrigin(shapeBounds.left + shapeBounds.width / 2,
                        shapeBounds.top + shapeBounds.height / 2);
        return shapeBounds;
    }

template <typename T1, typename T2>
    inline double dis(
        sf::Vector2<T1> node1,
        sf::Vector2<T2> node2) noexcept
    {
        return std::sqrt(
            std::pow(
                (
                    static_cast<double>(node1.x) -
                    static_cast<double>(node2.x)),
                2) +
            std::pow(
                (
                    static_cast<double>(node1.y) -
                    static_cast<double>(node2.y)),
                2));
}


#endif
