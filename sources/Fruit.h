#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace sfSnake
{
    class Fruit
    {
    public:
        Fruit(bool isHell);
        Fruit(const sf::Vector2f& snakeHeadPosition, bool isHell);

        void render(sf::RenderWindow& window);
        sf::FloatRect getBounds() const;
        int getScore() const; // 获取分值
        sf::Color getColor() const; // 获取颜色

    private:
        sf::CircleShape shape_;
        int score_; // 分值
        static const std::vector<sf::Color> colors_; // 果子颜色
        static const std::vector<int> scores_; // 果子分值
    };
}

#endif