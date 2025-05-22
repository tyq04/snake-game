#include "MenuScreen.h"
#include "DifficultyScreen.h"
#include "SettingsScreen.h"
#include "HelpScreen.h"
#include "MiniGameScreen.h"
#include "Game.h"

using namespace sfSnake;

extern std::shared_ptr<SettingsScreen> settingsScreen; // 外部声明设置界面的指针

MenuScreen::MenuScreen()
: playButton_(), // 初始化播放按钮
  settingsButton_(), // 初始化设置按钮
  helpButton_(), // 初始化帮助按钮
  miniGameButton_(), // 初始化小游戏按钮
  backButton_() // 初始化返回按钮
{
    playButton_.update("../img/playbutton.png"); // 加载并设置播放按钮的图像
    settingsButton_.update("../img/settingsbutton.png"); // 加载并设置设置按钮的图像
    helpButton_.update("../img/helpbutton.png"); // 加载并设置帮助按钮的图像
    miniGameButton_.update("../img/minigamebutton.png"); // 加载并设置小游戏按钮的图像
    backButton_.update("../img/homebutton.png"); // 加载并设置返回按钮的图像

    playButton_.setPosition(200, 360); // 设置播放按钮的位置
    settingsButton_.setPosition(400, 360); // 设置设置按钮的位置
    helpButton_.setPosition(600, 360); // 设置帮助按钮的位置
    miniGameButton_.setPosition(700, 100); // 设置小游戏按钮的位置
    backButton_.setPosition(700, 500); // 设置返回按钮的位置

    font_.loadFromFile("../Fonts/game_over.ttf"); // 加载字体文件
    titleText_.setFont(font_); // 设置标题文本的字体
    titleText_.setString("Snake Game"); // 设置标题文本内容
    titleText_.setCharacterSize(30); // 设置标题文本大小
    titleText_.setFillColor(sf::Color::White); // 设置标题文本颜色
    sf::FloatRect textBounds = titleText_.getLocalBounds(); // 获取标题文本的边界
    titleText_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2); // 设置标题文本的原点为中心
    titleText_.setPosition(Game::Width / 2, 100); // 设置标题文本的位置为屏幕中心偏上一些

    titleTexture_.loadFromFile("../img/logo.png"); // 加载标题图像的纹理
    titleSprite_.setTexture(titleTexture_); // 设置标题精灵的纹理
    titleSprite_.setPosition(50, 0); // 设置标题精灵的位置
    titleSprite_.setScale(0.7, 0.7); // 设置标题精灵的缩放比例
}

// 处理输入函数，处理鼠标点击事件
void MenuScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // 如果鼠标左键被按下
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window); // 获取鼠标当前位置

        if (playButton_.contain(mousePos)) // 如果鼠标位于播放按钮上
        {
            playButton_.focused(true); // 设置播放按钮为焦点状态
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // 如果再次左键被按下
            {
                Game::Screen = std::make_shared<DifficultyScreen>(); // 切换到难度选择界面
                sf::sleep(sf::seconds(0.2)); // 等待一段时间避免连续点击
            }
        }
        else if (settingsButton_.contain(mousePos)) // 如果鼠标位于设置按钮上
        {
            settingsButton_.focused(true); // 设置设置按钮为焦点状态
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // 如果再次左键被按下
            {
                Game::Screen = settingsScreen; // 切换到设置界面
                sf::sleep(sf::seconds(0.2)); // 等待一段时间避免连续点击
            }
        }
        else if (helpButton_.contain(mousePos)) // 如果鼠标位于帮助按钮上
        {
            helpButton_.focused(true); // 设置帮助按钮为焦点状态
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // 如果再次左键被按下
            {
                Game::Screen = std::make_shared<HelpScreen>(); // 切换到帮助界面
                sf::sleep(sf::seconds(0.2)); // 等待一段时间避免连续点击
            }
        }
        else if (miniGameButton_.contain(mousePos)) // 如果鼠标位于小游戏按钮上
        {
            miniGameButton_.focused(true); // 设置小游戏按钮为焦点状态
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // 如果再次左键被按下
            {
                Game::Screen = std::make_shared<MiniGameScreen>(); // 切换到小游戏界面
                sf::sleep(sf::seconds(0.2)); // 等待一段时间避免连续点击
            }
        }
        else if (backButton_.contain(mousePos)) // 如果鼠标位于返回按钮上
        {
            backButton_.focused(true); // 设置返回按钮为焦点状态
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // 如果再次左键被按下
            {
                window.close(); // 关闭窗口
            }
        }
    }
}

// 更新函数，静态菜单界面无需更新
void MenuScreen::update(sf::Time delta){}

// 渲染函数，绘制菜单界面的所有元素
void MenuScreen::render(sf::RenderWindow& window)
{
    window.draw(titleText_); // 绘制标题文本
    playButton_.render(window); // 绘制播放按钮
    settingsButton_.render(window); // 绘制设置按钮
    helpButton_.render(window); // 绘制帮助按钮
    miniGameButton_.render(window); // 绘制小游戏按钮
    backButton_.render(window); // 绘制返回按钮
    window.draw(titleSprite_); // 绘制标题精灵
}
