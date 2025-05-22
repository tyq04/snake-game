#include "DifficultyScreen.h"
#include "GameScreen.h"
#include "Game.h"
#include "MenuScreen.h"

using namespace sfSnake;

// 构造函数，初始化所有按钮并设置其位置和外观
DifficultyScreen::DifficultyScreen()
: beginnerButton_(),
  intermediateButton_(),
  advancedButton_(),
  hellButton_(),
  backButton_()
{
    // 更新按钮的纹理
    beginnerButton_.update("../img/beginer.png");
    intermediateButton_.update("../img/intermediate.png");
    advancedButton_.update("../img/advanced.png");
    hellButton_.update("../img/hell.png");
    backButton_.update("../img/backbutton.png");

    // 设置按钮的位置
    beginnerButton_.setPosition(400, 200);
    intermediateButton_.setPosition(400, 300);
    advancedButton_.setPosition(400, 400);
    hellButton_.setPosition(400, 500);
    backButton_.setPosition(100, 100);

    // 加载字体并设置标题文本的属性
    font_.loadFromFile("../Fonts/game_over.ttf");
    titleText_.setFont(font_);
    titleText_.setString("Select Difficulty");
    titleText_.setCharacterSize(30);
    titleText_.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = titleText_.getLocalBounds();
    titleText_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    titleText_.setPosition(Game::Width / 2, 100);
}

// 处理输入
void DifficultyScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // 检查每个按钮是否被点击
        if (beginnerButton_.contain(mousePos))
        {
            beginnerButton_.focused(true);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Game::Screen = std::make_shared<GameScreen>(Difficulty::Beginner);
            }
        }
        else if (intermediateButton_.contain(mousePos))
        {
            intermediateButton_.focused(true);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Game::Screen = std::make_shared<GameScreen>(Difficulty::Intermediate);
            }
        }
        else if (advancedButton_.contain(mousePos))
        {
            advancedButton_.focused(true);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Game::Screen = std::make_shared<GameScreen>(Difficulty::Advanced);
            }
        }
        else if (hellButton_.contain(mousePos))
        {
            hellButton_.focused(true);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Game::Screen = std::make_shared<GameScreen>(Difficulty::Hell);
            }
        }
        else if (backButton_.contain(mousePos))
        {
            backButton_.focused(true);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Game::Screen = std::make_shared<MenuScreen>();
            }
        }
    }
}

// 更新函数，对于静态设置界面不需要更新
void DifficultyScreen::update(sf::Time delta){}


// 渲染函数，绘制标题文本和所有按钮
void DifficultyScreen::render(sf::RenderWindow& window)
{
    window.draw(titleText_);
    beginnerButton_.render(window);
    intermediateButton_.render(window);
    advancedButton_.render(window);
    hellButton_.render(window);
    backButton_.render(window);
}
