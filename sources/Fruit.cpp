#include "Fruit.h"
#include "Game.h"
#include <cmath>
#include <random>

using namespace sfSnake;

// 定义静态成员变量，果子的颜色和分数
const std::vector<sf::Color> Fruit::colors_ = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta};
const std::vector<int> Fruit::scores_ = {1, 2, 3, 4, 5};

// 随机数生成器和分布
static std::default_random_engine random(time(NULL));
std::uniform_int_distribution<unsigned> disFruit(0, 4); // 随机选择一种颜色和分数
std::uniform_int_distribution<int> disWidth(100, Game::Width - 100); // 随机选择果子在屏幕宽度中的位置
std::uniform_int_distribution<int> disHeight(100, Game::Height - 100); // 随机选择果子在屏幕高度中的位置

// 构造函数，初始化果子
Fruit::Fruit(bool isHell)
{
    int index = disFruit(random); // 随机选择一种颜色和分数
    shape_.setFillColor(colors_[index]);
    score_ = scores_[index];

    // 根据难度设置果子的半径
    shape_.setRadius((25 - 3 * score_) / (1 + isHell));

    // 随机设置果子的位置
    shape_.setPosition(
        disWidth(random),
        disHeight(random));
}

// 带有蛇头位置的构造函数，确保果子不会生成在蛇头附近
Fruit::Fruit(const sf::Vector2f& snakeHeadPosition, bool isHell)
{
    int index = disFruit(random); // 随机选择一种颜色和分数
    shape_.setFillColor(colors_[index]);
    score_ = scores_[index];

    // 根据难度设置果子的半径
    shape_.setRadius((25 - 3 * score_) / (1 + isHell));

    sf::Vector2f position;
    // 生成位置，确保果子不在蛇头100像素的范围内
    do {
        position = sf::Vector2f(
        disWidth(random),
        disHeight(random));
    } while (std::sqrt(std::pow(position.x - snakeHeadPosition.x, 2) + std::pow(position.y - snakeHeadPosition.y, 2)) < 100);

    shape_.setPosition(position);
}

// 在窗口中渲染果子
void Fruit::render(sf::RenderWindow& window)
{
    window.draw(shape_);
}

// 获取果子的边界
sf::FloatRect Fruit::getBounds() const
{
    return shape_.getGlobalBounds();
}

// 获取果子的分数
int Fruit::getScore() const
{
    return score_;
}

// 获取果子的颜色
sf::Color Fruit::getColor() const
{
    return shape_.getFillColor();
}
