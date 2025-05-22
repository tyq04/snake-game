#include "SettingsScreen.h"
#include "Game.h"
#include "MenuScreen.h"

using namespace sfSnake;

SettingsScreen::SettingsScreen()
: backgroundColor_(sf::Color::White), gridEnabled_(false), gridColor_(sf::Color::Black),
  blackBgButton_(),
  whiteBgButton_(),
  brownBgButton_(),
  toggleGridButton_(),
  blackGridButton_(),
  whiteGridButton_(),
  brownGridButton_(),
  backButton_()//初始化成员变量
{
    //加载图片
    blackBgButton_.update("../img/blackbgbutton.png");
    whiteBgButton_.update("../img/whitebgbutton.png");
    brownBgButton_.update("../img/brownbgbutton.png");
    toggleGridButton_.update("../img/togglegridbutton.png");
    blackGridButton_.update("../img/blackgridbutton.png");
    whiteGridButton_.update("../img/whitegridbutton.png");
    brownGridButton_.update("../img/browngridbutton.png");
    backButton_.update("../img/backbutton.png");

    //设置图片位置
    blackBgButton_.setPosition(600,200);
    whiteBgButton_.setPosition(200,200);
    brownBgButton_.setPosition(400,200);
    toggleGridButton_.setPosition(200,300);
    blackGridButton_.setPosition(600,400);
    whiteGridButton_.setPosition(200,400);
    brownGridButton_.setPosition(400,400);
    backButton_.setPosition(100,100);

    //设置文字
    font_.loadFromFile("../Fonts/game_over.ttf");
    titleText_.setFont(font_);
    titleText_.setString("Settings");
    titleText_.setCharacterSize(30);
    titleText_.setFillColor(sf::Color::Black);
    sf::FloatRect textBounds = titleText_.getLocalBounds();
    titleText_.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
    titleText_.setPosition(Game::Width / 2, 50);
}

//处理输入
void SettingsScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        //设置背景颜色
        if (blackBgButton_.contain(mousePos))
        {
            blackBgButton_.focused(true);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                backgroundColor_ = sf::Color::Black;
            }
        }
        else if (whiteBgButton_.contain(mousePos))
        {
            whiteBgButton_.focused(true);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                backgroundColor_ = sf::Color::White;
            }
        }
        else if (brownBgButton_.contain(mousePos))
        {
            brownBgButton_.focused(true);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                backgroundColor_ = Game::Color::Background[2];
            }
        }
        //设置网格开关
        else if (toggleGridButton_.contain(mousePos))
        {
            toggleGridButton_.focused(true);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                gridEnabled_ = !gridEnabled_;
            }
        }
        //设置网格颜色
        else if (blackGridButton_.contain(mousePos))
        {
            blackGridButton_.focused(true);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                gridColor_ = sf::Color::Black;
            }
        }
        else if (whiteGridButton_.contain(mousePos))
        {
            whiteGridButton_.focused(true);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                gridColor_ = sf::Color::White;
            }
        }
        else if (brownGridButton_.contain(mousePos))
        {
            brownGridButton_.focused(true);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                gridColor_ = Game::Color::Grid[2];
            }
        }
        //返回按钮
        else if (backButton_.contain(mousePos))
        {
            backButton_.focused(true);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                Game::Screen = std::make_shared<MenuScreen>();
            }
        }
    }
}

void SettingsScreen::update(sf::Time delta){}

void SettingsScreen::render(sf::RenderWindow& window)
{   
    //绘制稳字与按钮
    window.draw(titleText_);
    blackBgButton_.render(window);
    whiteBgButton_.render(window);
    brownBgButton_.render(window);
    toggleGridButton_.render(window);
    blackGridButton_.render(window);
    whiteGridButton_.render(window);
    brownGridButton_.render(window);
    backButton_.render(window);
}

sf::Color SettingsScreen::getBackgroundColor() const
{
    return backgroundColor_;
}

bool SettingsScreen::isGridEnabled() const
{
    return gridEnabled_;
}

sf::Color SettingsScreen::getGridColor() const
{
    return gridColor_;
}
