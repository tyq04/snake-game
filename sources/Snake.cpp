#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>
#include <vector>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "DifficultyScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;
sf::Vector2f vectorRotate(const sf::Vector2f& v, double angleDegrees);

Snake::Snake() : direction_(sf::Vector2f(1, 0)), hitSelf_(false), moveTimer_(sf::Time::Zero), score_(0)
{
    initNodes();

    pickupBuffer_.loadFromFile("../Sounds/pickup.aiff");
    pickupSound_.setBuffer(pickupBuffer_);
    pickupSound_.setVolume(30);

    dieBuffer_.loadFromFile("../Sounds/die.wav");
    dieSound_.setBuffer(dieBuffer_);
    dieSound_.setVolume(50);
}

void Snake::initNodes()//初始化蛇节点
{
    for (int i = 0; i < Snake::InitialSize; i++)
    {
        if (i == 0)//第一个蛇节点为头节点
        {
            nodes_.push_back(SnakeNode(sf::Vector2f(
                Game::Width / 2 - SnakeNode::Width / 2,
                Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i)), true, sf::Color::Red));
        }
        else
        {
            nodes_.push_back(SnakeNode(sf::Vector2f(
                Game::Width / 2 - SnakeNode::Width / 2,
                Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i)), false, sf::Color::Red));
        }
    }
}

void Snake::handleInput(const sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
        sf::Vector2f head_position = nodes_[0].getPosition(); // 获取蛇头的位置
        sf::Vector2f body1_position = nodes_[1].getPosition();//获取第一节身体的位置，以获取上一时刻的方向

        direction_.x = mouse_position.x - head_position.x;
        direction_.y = mouse_position.y - head_position.y;

        olddirection_.x = head_position.x - body1_position.x;
        olddirection_.y = head_position.y - body1_position.y;

        float length_d = sqrt(direction_.x * direction_.x + direction_.y * direction_.y);
        if (length_d != 0) {
            direction_.x /= length_d;
            direction_.y /= length_d;
        }

        float length_od = sqrt(olddirection_.x * olddirection_.x + olddirection_.y * olddirection_.y);
        olddirection_ = {olddirection_.x / length_od, olddirection_.y / length_od};

        float dot = direction_.x * olddirection_.x + direction_.y * olddirection_.y; // 点积
        float det = olddirection_.x * direction_.y - olddirection_.y * direction_.x; // 叉积
        float turnangle = atan2(det, dot) * 180 / 3.14159265;
        if(dis(nodes_[0].getPosition(),nodes_[1].getPosition()) < 100)
        {if(turnangle > 3){
            direction_ = vectorRotate(olddirection_, 3);//强制使蛇慢转向
        }
        else if(turnangle < -3){
            direction_ = vectorRotate(olddirection_, -3);//强制使蛇慢转向
        }}

        float angle = atan2(direction_.y, direction_.x) * 180 / 3.14159265;
        nodes_[0].setRotation(angle + 90);
    }
}

void Snake::update(sf::Time delta, std::vector<Fruit>& fruits, Difficulty& difficulty)//更新
{
    moveTimer_ += delta;
    if (moveTimer_ >= updateInterval_)
    {
        move();//移动
        checkEdgeCollisions();//查询是否撞到边缘
        checkSelfCollisions();//查询是否撞到自己
		checkFruitCollisions(fruits, difficulty);//查询是否吃到果子
        moveTimer_ = sf::Time::Zero; // 重置计时器
    }
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits, Difficulty& difficulty)
{
    auto toRemove = fruits.end();
    sf::Color newNodeColor;
	difficulty_ = difficulty;

    for (auto it = fruits.begin(); it != fruits.end(); ++it)
    {
        if (it->getBounds().intersects(nodes_[0].getBounds())) {
            toRemove = it;
            newNodeColor = it->getColor(); // 获取果子的颜色
            break;
        }
    }

    if (toRemove != fruits.end())
    {
        pickupSound_.play();
        score_ += toRemove->getScore(); // 增加分数
        grow(newNodeColor); // 传递颜色
        fruits.erase(toRemove);//移除果子
        fruits.push_back(Fruit(nodes_[0].getPosition(), difficulty == Difficulty::Hell)); // 生成新的果子，传递蛇头位置
    }

}

void Snake::grow(sf::Color color)
{
    for(int i = 0; i < 4; i++){//长四个节点，显示其中一个，以避免蛇太拥挤
    SnakeNode& tailNode = nodes_.back();
    sf::Vector2f newPosition = tailNode.getPosition();
    newPosition.x -= direction_.x * SnakeNode::Width * 0.05f * (4 + int(difficulty_));
    newPosition.y -= direction_.y * SnakeNode::Height * 0.05f * (4 + int(difficulty_));

    nodes_.push_back(SnakeNode(newPosition, false, color)); // 使用颜色构造新的节点
    }
}

unsigned Snake::getSize() const
{
    return nodes_.size();
}

unsigned Snake::getScore() const
{
    return score_;
}

bool Snake::hitSelf() const
{
    return hitSelf_;
}

sf::Vector2f Snake::getPosition() const
{
    if (nodes_.empty())
        return sf::Vector2f(0, 0);

    return nodes_[0].getPosition();
}

void Snake::checkSelfCollisions()
{
    SnakeNode& headNode = nodes_[0];

    for (size_t i = 25; i < nodes_.size(); ++i)//从25开始，避免误判，因为缓转机制的存在，不可能撞到25格以内的自己
    {
        if (headNode.getBounds().intersects(nodes_[i].getBounds()))
        {
            dieSound_.play();
            sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
            hitSelf_ = true;
            return;
        }
    }
}

void Snake::checkEdgeCollisions()//边缘穿墙
{
    SnakeNode& headNode = nodes_[0];

    if (headNode.getPosition().x < 0)
        headNode.setPosition(Game::Width, headNode.getPosition().y);
    else if (headNode.getPosition().x >= Game::Width)
        headNode.setPosition(0, headNode.getPosition().y);
    else if (headNode.getPosition().y < 0)
        headNode.setPosition(headNode.getPosition().x, Game::Height);
    else if (headNode.getPosition().y >= Game::Height)
        headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()//移动
{
    const float moveFactor = 0.05f * (4 + int(difficulty_)); // 调整移动因子来减速
    for (size_t i = nodes_.size() - 1; i > 0; --i)
    {
        nodes_[i].setPosition(nodes_[i - 1].getPosition());//继承上一个节点的位置
    }

    nodes_[0].move(direction_.x * SnakeNode::Width * moveFactor, direction_.y * SnakeNode::Height * moveFactor);//头向direction方向移动
	}

void Snake::render(sf::RenderWindow& window)
{
	nodes_[0].render(window);
	int node_size = nodes_.size();
    for (int i = 5; i < node_size; i += 4-int(difficulty_)/2)//从头节点后的第五个节点开始显示，每四个显示一次
    {
        nodes_[i].render(window);
    }
}

SnakeNode Snake::getHead() const
{
	return nodes_[0];
}

sf::Vector2f vectorRotate(const sf::Vector2f& v, double angleDegrees)//向量转动
{
    double angleRadians = angleDegrees * (3.14159265 / 180.0);
    double cosTheta = std::cos(angleRadians);
    double sinTheta = std::sin(angleRadians);

    sf::Vector2f result;
    result.x = v.x * cosTheta - v.y * sinTheta;
    result.y = v.x * sinTheta + v.y * cosTheta;

    return result;
}
