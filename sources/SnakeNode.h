#ifndef SNAKENODE_H
#define SNAKENODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
    class SnakeNode
    {
    public:
        SnakeNode(sf::Vector2f position, bool isHead, sf::Color color = sf::Color::Green); // 添加isHead和颜色参数

        void setPosition(sf::Vector2f position);
        void setPosition(float x, float y);
        void move(float xOffset, float yOffset);
        void setRotation(float angle);
        sf::FloatRect getBounds() const;
        sf::Vector2f getPosition() const;
        void render(sf::RenderWindow& window);

        static const float Width;
        static const float Height;

    private:
        sf::Vector2f position_;
        sf::RectangleShape shape_;
        sf::CircleShape bodyShape_;
        bool isHead_;
        //sf::Texture headTexture_;
        sf::Sprite headSprite_;
    };
}

#endif
