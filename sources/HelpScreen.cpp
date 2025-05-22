#include "HelpScreen.h"
#include "Game.h"
#include "MenuScreen.h"

using namespace sfSnake;

// HelpScreen 类的构造函数
HelpScreen::HelpScreen()
: backButton_() // 初始化返回按钮
{
    backButton_.update("../img/backbutton.png"); // 加载并设置返回按钮的图像
    backButton_.setPosition(100,100); // 设置返回按钮的位置

    font_.loadFromFile("../Fonts/game_over.ttf"); // 加载字体文件
    helpText_.setFont(font_); // 设置帮助文本的字体
    helpText_.setString(
        "Help Information:\n"
        "1. Use the mouse to control the snake.\n" // 控制蛇使用鼠标
        "2. Collect fruits to grow the snake.\n" // 收集水果来增长蛇
        "3. Avoid hitting the snake itself.\n" // 避免撞到蛇自身
        "4. Press buttons/esc to pause or exit the game."); // 按钮/ESC键暂停或退出游戏
    helpText_.setCharacterSize(20); // 设置字体大小
    helpText_.setFillColor(sf::Color::Black); // 设置文本颜色为黑色
    sf::FloatRect textBounds = helpText_.getLocalBounds(); // 获取文本的边界
    helpText_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2); // 设置文本的原点为中心
    helpText_.setPosition(Game::Width / 2, Game::Height / 2 - 100); // 设置文本的位置为屏幕中心偏上一些
}

// 处理输入函数，处理鼠标点击事件
void HelpScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // 如果左键被按下
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); // 获取鼠标当前位置

        if (backButton_.contain(mousePos)) // 如果鼠标位于返回按钮上
        {
            backButton_.focused(true); // 设置返回按钮为焦点状态
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ // 如果再次左键被按下
                Game::Screen = std::make_shared<MenuScreen>(); // 切换到菜单界面
            }
        }
    }
}

// 更新函数，静态帮助界面不需要更新
void HelpScreen::update(sf::Time delta)
{
    // 静态帮助界面无需更新
}

// 渲染函数，绘制帮助文本和返回按钮
void HelpScreen::render(sf::RenderWindow& window)
{
    window.draw(helpText_); // 绘制帮助文本
    backButton_.render(window); // 绘制返回按钮
}
