#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "SnakeNode.h"
#include "Fruit.h"
#include "DifficultyScreen.h"

namespace sfSnake
{
    class Snake
    {
    public:
        Snake();

        void handleInput(const sf::RenderWindow& window);
        void update(sf::Time delta, std::vector<Fruit>& fruits, Difficulty& difficulty);
        void render(sf::RenderWindow& window);

        void checkFruitCollisions(std::vector<Fruit>& fruits, Difficulty& difficulty);
        void grow(sf::Color color);
        unsigned getSize() const;
        bool hitSelf() const;
        unsigned getScore() const; // 获取分数
        sf::Vector2f getPosition() const; // 获取蛇头位置
        SnakeNode getHead() const;

    private:
        void initNodes();
        void move();
        void checkSelfCollisions();
        void checkEdgeCollisions();

        std::vector<SnakeNode> nodes_;
        sf::Vector2f direction_;
        sf::Vector2f olddirection_;
        bool hitSelf_;
        static const int InitialSize;

        sf::SoundBuffer pickupBuffer_;
        sf::Sound pickupSound_;
        sf::SoundBuffer dieBuffer_;
        sf::Sound dieSound_;
        Difficulty difficulty_;

        sf::Time moveTimer_;
        const sf::Time updateInterval_ = sf::seconds(0.02f); // 调整更新间隔来减速

        unsigned score_; // 分数
    };
}

#endif
