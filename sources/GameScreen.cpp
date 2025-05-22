#include "GameScreen.h"
#include "PauseScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

extern std::shared_ptr<SettingsScreen> settingsScreen;

// 构造函数，初始化游戏屏幕
GameScreen::GameScreen(Difficulty difficulty)
: smallFruits_(false)
{
    font_.loadFromFile("../Fonts/game_over.ttf");

    // 获取设置界面的背景颜色和网格设置
    backgroundColor_ = settingsScreen->getBackgroundColor();
    gridEnabled_ = settingsScreen->isGridEnabled();
    gridColor_ = settingsScreen->getGridColor();
    
    // 设置分数文本的字体和颜色
    scoreText_.setFont(font_);
    if (backgroundColor_ != sf::Color::White)
        scoreText_.setFillColor(sf::Color::White);
    else
        scoreText_.setFillColor(sf::Color::Black);
    scoreText_.setPosition(10, 10);
    
    // 根据难度设置蛇的速度和果子大小
    difficulty_ = difficulty;
    switch (difficulty)
    {
        case Difficulty::Beginner:
            snakeSpeed_ = 0.5f;
            break;
        case Difficulty::Intermediate:
            snakeSpeed_ = 0.35f;
            break;
        case Difficulty::Advanced:
            snakeSpeed_ = 0.2f;
            break;
        case Difficulty::Hell:
            snakeSpeed_ = 0.1f;
            smallFruits_ = true;
            break;
    }

    // 初始化果子
    initFruits(difficulty);
}

// 处理输入
void GameScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        // 按下ESC键，切换到暂停界面
        Game::Screen = std::make_shared<PauseScreen>(std::static_pointer_cast<GameScreen>(Game::Screen));
    }
    else
    {
        // 处理蛇的输入
        snake_.handleInput(window);
    }
}

// 更新游戏状态
void GameScreen::update(sf::Time delta)
{
    // 更新蛇的状态
    snake_.update(delta, fruits_, difficulty_);

    // 检查蛇是否撞到自己
    if (snake_.hitSelf())
        Game::Screen = std::make_shared<GameOverScreen>(snake_.getScore());

    // 更新分数
    updateScore();
}

// 渲染游戏
void GameScreen::render(sf::RenderWindow& window)
{
    // 清除窗口并设置背景颜色
    window.clear(backgroundColor_);

    // 如果启用了网格，则绘制网格
    if (gridEnabled_)
        drawGrid(window);

    // 渲染蛇和果子
    snake_.render(window);
    for (auto& fruit : fruits_)
        fruit.render(window);

    // 渲染分数文本
    window.draw(scoreText_);
}

// 初始化果子
void GameScreen::initFruits(Difficulty difficulty)
{
    for (int i = 0; i < 5; ++i)
    {
        Fruit fruit(snake_.getPosition(), difficulty == Difficulty::Hell);
        fruits_.push_back(fruit);
    }
}

// 更新分数文本
void GameScreen::updateScore()
{
    scoreText_.setString("Score: " + std::to_string(snake_.getScore()));
}

// 绘制网格
void GameScreen::drawGrid(sf::RenderWindow& window)
{
    sf::RectangleShape line(sf::Vector2f(Game::Width, 1));
    line.setFillColor(gridColor_);

    for (int y = 0; y < Game::Height; y += 30)
    {
        line.setPosition(0, y);
        window.draw(line);
    }

    line.setSize(sf::Vector2f(1, Game::Height));
    for (int x = 0; x < Game::Width; x += 30)
    {
        line.setPosition(x, 0);
        window.draw(line);
    }
}

// 获取当前难度
Difficulty GameScreen::getDifficulty()
{
    return difficulty_;
}

// 获取蛇对象
Snake GameScreen::getSnake() const
{
    return snake_;
}
