#include "PauseScreen.h"
#include "Game.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Snake.h"

using namespace sfSnake;

PauseScreen::PauseScreen(std::shared_ptr<GameScreen> gameScreen)
: gameScreen_(gameScreen),
  restartButton(),
  MenuButton(),
  continueButton()
{
    restartButton.update("../img/restart.png"); // 更新重新开始按钮的图像
    MenuButton.update("../img/homebutton.png"); // 更新返回菜单按钮的图像
    continueButton.update("../img/playbutton.png"); // 更新继续按钮的图像

    restartButton.setPosition(400,360); // 设置重新开始按钮的位置
    MenuButton.setPosition(600,360); // 设置返回菜单按钮的位置
    continueButton.setPosition(200,360); // 设置继续按钮的位置

    font_.loadFromFile("../Fonts/game_over.ttf"); // 加载游戏结束字体文件

    text_.setFont(font_); // 设置文本字体
    text_.setString("Paused"); // 设置文本内容为 "Paused"
    sf::FloatRect textBounds = text_.getLocalBounds(); // 获取文本的本地边界
    text_.setOrigin(textBounds.left + textBounds.width / 2,
                    textBounds.top + textBounds.height / 2); // 设置文本的原点为中心点
    text_.setPosition(Game::Width / 2, Game::Height / 4); // 设置文本位置居中
    text_.setFillColor(sf::Color::Black); // 设置文本颜色为黑色
}


void PauseScreen::handleInput(sf::RenderWindow& window)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ // 如果鼠标左键被按下
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); // 获取鼠标当前位置

        if(continueButton.contain(mousePos)){ // 如果鼠标在继续按钮区域内
            continueButton.focused(true); // 设置继续按钮为选中状态
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ // 如果继续按钮被点击
                Game::Screen = gameScreen_; // 回到游戏界面
                sf::sleep(sf::seconds(0.2)); // 等待一小段时间，避免立即重复点击
            }
        }

        else if(restartButton.contain(mousePos)){ // 如果鼠标在重新开始按钮区域内
            restartButton.focused(true); // 设置重新开始按钮为选中状态
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ // 如果重新开始按钮被点击
                Game::Screen = std::make_shared<GameScreen>(gameScreen_->getDifficulty()); // 创建一个新的游戏界面
            }
        }

        else if(MenuButton.contain(mousePos)){ // 如果鼠标在返回菜单按钮区域内
            MenuButton.focused(true); // 设置返回菜单按钮为选中状态
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){ // 如果返回菜单按钮被点击
                Game::Screen = std::make_shared<MenuScreen>(); // 切换到菜单界面
                sf::sleep(sf::seconds(0.2)); // 等待一小段时间，避免立即重复点击
            }
        }
    }
}

void PauseScreen::update(sf::Time delta)
{
    // 暂停界面不需要更新逻辑
}

void PauseScreen::render(sf::RenderWindow& window)
{
    window.draw(text_); // 绘制 "Paused" 文本
    restartButton.render(window); // 绘制重新开始按钮
    continueButton.render(window); // 绘制继续按钮
    MenuButton.render(window); // 绘制返回菜单按钮
}
