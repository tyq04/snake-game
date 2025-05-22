#include "GameOverScreen.h"
#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

// 构造函数，初始化按钮并设置游戏结束文本
GameOverScreen::GameOverScreen(unsigned score)
: menuButton_(), exitButton_()
{
    // 更新按钮的纹理
    menuButton_.update("../img/backbutton.png");
    exitButton_.update("../img/homebutton.png");

    // 设置按钮的位置
    menuButton_.setPosition(250, 360);
    exitButton_.setPosition(550, 360);

    // 加载字体并设置文本属性
    font_.loadFromFile("../Fonts/game_over.ttf");
    text_.setFont(font_);
    text_.setString("Game Over!\n\nScore: " + std::to_string(score));

    // 设置文本的原点到中心位置
    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
                    textBounds.top + textBounds.height / 2);
    text_.setPosition(Game::Width / 2, Game::Height / 4);
    text_.setFillColor(sf::Color::Black);
}

// 处理输入
void GameOverScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // 检查每个按钮是否被点击
        if (menuButton_.contain(mousePos))
        {
            menuButton_.focused(true);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Game::Screen = std::make_shared<MenuScreen>();
                sf::sleep(sf::seconds(0.2));
            }
        }
        else if (exitButton_.contain(mousePos))
        {
            exitButton_.focused(true);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                window.close();
            }
        }
    }
}

// 更新函数，对于静态游戏结束屏幕不需要更新
void GameOverScreen::update(sf::Time delta)
{
    // 游戏结束屏幕不需要更新
}

// 渲染函数，绘制文本和所有按钮
void GameOverScreen::render(sf::RenderWindow& window)
{
    window.draw(text_);
    menuButton_.render(window);
    exitButton_.render(window);
}
