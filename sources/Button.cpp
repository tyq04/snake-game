#include "Button.h"
#include "Game.h"

using namespace sfSnake;

// 构造函数，初始化按钮的聚焦状态为false
Button::Button()
    : focused_{false}
{
}

// 更新按钮的纹理和缩放
void Button::update(std::string filename, float scale)
{
    // 从文件中加载纹理，如果加载失败则返回
    if (!texture_.loadFromFile(filename))
        return;
    texture_.setSmooth(true); // 设置纹理平滑
    sprite_.setTexture(texture_); // 将纹理设置为精灵的纹理
    sf::FloatRect bounds = setOriginMiddle(sprite_); // 设置精灵的原点到中心
    sprite_.setScale(0.1, 0.1); // 设置精灵缩放
}

// 设置按钮的位置
void Button::setPosition(float x, float y)
{
    sprite_.setPosition(x, y); // 设置精灵的位置
}

// 设置按钮的聚焦状态，并改变按钮的颜色
void Button::focused(bool status)
{
    focused_ = status; // 更新聚焦状态
    if (status)
        sprite_.setColor(sf::Color::Green); // 如果聚焦，则设置颜色为绿色
    else
        sprite_.setColor(sf::Color::White); // 如果未聚焦，则设置颜色为白色
}

// 获取按钮的聚焦状态
bool Button::focused() const
{
    return focused_; // 返回聚焦状态
}

// 渲染按钮
void Button::render(sf::RenderWindow &window) const
{
    window.draw(sprite_); // 在窗口中绘制精灵
}
