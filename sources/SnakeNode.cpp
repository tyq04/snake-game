#include "SnakeNode.h"
#include "Game.h"
#include <iostream>

using namespace sfSnake;
static sf::Texture headTexture_;
const float SnakeNode::Width = 10.f;
const float SnakeNode::Height = 10.f;

SnakeNode::SnakeNode(sf::Vector2f position, bool isHead, sf::Color color)
    : position_(position), isHead_(isHead)
{
    if (isHead_) {//是头节点，则加载精灵并进行精灵的设置
        if (!headTexture_.loadFromFile("../img/head.png")) {
            std::cerr << "Error loading head.png" << std::endl;
        } else {
            headTexture_.setSmooth(true);
            headSprite_.setTexture(headTexture_);
            sf::Vector2u textureSize = headTexture_.getSize();
            float headScale = SnakeNode::Width / textureSize.y * 2;
            headSprite_.setScale(headScale, headScale);
            headSprite_.setOrigin(headTexture_.getSize().x /2, headTexture_.getSize().y/2);
            headSprite_.setPosition(position_);
        }
    } else {//否则加载身体并进行身体的设置
        bodyShape_.setRadius(SnakeNode::Width / 2);
        bodyShape_.setFillColor(color);
        bodyShape_.setPosition(position_);

        shape_.setFillColor(sf::Color::Black);
        shape_.setSize(sf::Vector2f(SnakeNode::Width, 0.2 * SnakeNode::Height));
        shape_.setPosition(sf::Vector2f(position_.x - 15, position_.y));
    }
}


void SnakeNode::setPosition(sf::Vector2f position)
{
    position_ = position;
    if (isHead_) {
        headSprite_.setPosition(position_);
    } else {
        bodyShape_.setPosition(position_);
        shape_.setPosition(position_);
    }
}

void SnakeNode::setPosition(float x, float y)
{
    setPosition(sf::Vector2f(x, y));
}

void SnakeNode::move(float xOffset, float yOffset)
{
    setPosition(position_.x + xOffset, position_.y + yOffset);
}

void SnakeNode::setRotation(float angle)
{
    if (isHead_)
        headSprite_.setRotation(angle);
}

sf::FloatRect SnakeNode::getBounds() const
{
    if (isHead_) {
        return headSprite_.getGlobalBounds();
    } else {
        return shape_.getGlobalBounds();
    }
}

sf::Vector2f SnakeNode::getPosition() const
{
    return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
    if (isHead_) {
        window.draw(headSprite_);
    } else {
		window.draw(bodyShape_);
    }
}
