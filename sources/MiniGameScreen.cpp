#include "MiniGameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#include <cstdlib>
#include <ctime>
#include "MenuScreen.h"
#include "DifficultyScreen.h"

using namespace sfSnake;

extern std::shared_ptr<SettingsScreen> settingsScreen; // 外部声明设置界面的指针

MiniGameScreen::MiniGameScreen()
{
    font_.loadFromFile("../Fonts/game_over.ttf"); // 加载游戏结束字体文件


    backgroundColor_ = settingsScreen->getBackgroundColor(); // 获取背景颜色设置
    gridEnabled_ = settingsScreen->isGridEnabled(); // 获取是否显示网格设置
    gridColor_ = settingsScreen->getGridColor(); // 获取网格颜色设置

    scoreText_.setFont(font_); // 设置分数文本的字体
    if(backgroundColor_ != sf::Color::White)
        scoreText_.setFillColor(sf::Color::White); // 设置分数文本颜色为反色
    else
        scoreText_.setFillColor(sf::Color::Black);
    scoreText_.setPosition(10, 10); // 设置分数文本位置

    initWalls(); // 初始化墙壁
    initObstacles(); // 初始化障碍物
    initFruits(); // 初始化果子
}

void MiniGameScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // 如果按下了 Esc 键
    {
        Game::Screen = std::make_shared<MenuScreen>(); // 切换到菜单界面
    }
    else
    {
        snake_.handleInput(window); // 处理蛇的输入
    }
}

void MiniGameScreen::update(sf::Time delta)
{
    Difficulty difficulty = Difficulty::Intermediate; // 设置难度为中级

    snake_.update(delta, fruits_, difficulty); // 更新蛇的位置和状态
    
    checkObstacleCollisions(); // 检查蛇与障碍物的碰撞
    checkWallCollisions(); // 检查蛇与墙壁的碰撞

    if (snake_.hitSelf()) // 如果蛇撞到了自己
        Game::Screen = std::make_shared<GameOverScreen>(snake_.getScore()); // 切换到游戏结束界面

    updateScore(); // 更新分数显示
}

void MiniGameScreen::render(sf::RenderWindow& window)
{
    window.clear(backgroundColor_); // 清空窗口并设置背景色

    if (gridEnabled_) // 如果网格可见
        drawGrid(window); // 绘制网格

    snake_.render(window); // 绘制蛇

    for (auto& fruit : fruits_) // 遍历并绘制所有果子
        fruit.render(window);

    for (auto& obstacle : obstacles_) // 遍历并绘制所有障碍物
        window.draw(obstacle);

    for (auto& wall : walls_) // 遍历并绘制所有墙壁
        window.draw(wall);

    window.draw(scoreText_); // 绘制分数文本
}

void MiniGameScreen::initFruits()
{
    for (int i = 0; i < 5; ++i)
    {
        fruits_.push_back(Fruit(snake_.getPosition(), false)); // 将果子添加到果子数组中
    }
}

void MiniGameScreen::initObstacles()
{
    srand(static_cast<unsigned>(time(0)));
    int obstacleCount = 10;

    for (int i = 0; i < obstacleCount; ++i)
    {
        float width = 30.0f + rand() % 60; // 障碍物宽度在30到90之间
        float height = 30.0f;
        float x = static_cast<float>(rand() % (Game::Width - static_cast<int>(width)));
        float y = static_cast<float>(rand() % (Game::Height - static_cast<int>(height)));

        // 确保障碍物不生成在蛇的初始位置
        if ((x < Game::Width / 2 + 100 && x > Game::Width / 2 - 100) && (y < Game::Height / 2 + 100 && y > Game::Height / 2 - 100))
        {
            i--;
            continue;
        }

        sf::RectangleShape obstacle(sf::Vector2f(width, height));
        obstacle.setPosition(x, y);
        obstacle.setFillColor(sf::Color::Red);

        obstacles_.push_back(obstacle);
    }
}

void MiniGameScreen::initWalls()
{
    float wallThickness = 10.0f; // 墙壁厚度

    // 顶部墙壁
    sf::RectangleShape topWall(sf::Vector2f(Game::Width, wallThickness));
    topWall.setPosition(0, 0);
    topWall.setFillColor(sf::Color::Blue);
    walls_.push_back(topWall);

    // 底部墙壁
    sf::RectangleShape bottomWall(sf::Vector2f(Game::Width, wallThickness));
    bottomWall.setPosition(0, Game::Height - wallThickness);
    bottomWall.setFillColor(sf::Color::Blue);
    walls_.push_back(bottomWall);

    // 左侧墙壁
    sf::RectangleShape leftWall(sf::Vector2f(wallThickness, Game::Height));
    leftWall.setPosition(0, 0);
    leftWall.setFillColor(sf::Color::Blue);
    walls_.push_back(leftWall);

    // 右侧墙壁
    sf::RectangleShape rightWall(sf::Vector2f(wallThickness, Game::Height));
    rightWall.setPosition(Game::Width - wallThickness, 0);
    rightWall.setFillColor(sf::Color::Blue);
    walls_.push_back(rightWall);
}

void MiniGameScreen::updateScore()
{
    scoreText_.setString("Score: " + std::to_string(snake_.getScore())); // 更新分数文本的内容
}

void MiniGameScreen::checkObstacleCollisions()
{
    sf::FloatRect snakeHeadBounds = snake_.getHead().getBounds(); // 获取蛇头的边界

    for (auto& obstacle : obstacles_) // 遍历所有障碍物
    {
        if (snakeHeadBounds.intersects(obstacle.getGlobalBounds())) // 如果蛇头与障碍物相交
        {
            sf::sleep(sf::seconds(1));
            Game::Screen = std::make_shared<GameOverScreen>(snake_.getScore()); // 切换到游戏结束界面
            break;
        }
    }
}

void MiniGameScreen::checkWallCollisions()
{
    sf::FloatRect snakeHeadBounds = snake_.getHead().getBounds(); // 获取蛇头的边界

    for (auto& wall : walls_) // 遍历所有墙壁
    {
        if (snakeHeadBounds.intersects(wall.getGlobalBounds())) // 如果蛇头与墙壁相交
        {
            Game::Screen = std::make_shared<GameOverScreen>(snake_.getScore()); // 切换到游戏结束界面
            break;
        }
    }
}

void MiniGameScreen::drawGrid(sf::RenderWindow& window)
{
    sf::RectangleShape line(sf::Vector2f(Game::Width, 1));
    line.setFillColor(gridColor_); // 设置网格线的颜色

    // 绘制水平网格线
    for (int y = 0; y < Game::Height; y += 30)
    {
        line.setPosition(0, y);
        window.draw(line);
    }

    line.setSize(sf::Vector2f(1, Game::Height));

    // 绘制垂直网格线
    for (int x = 0; x < Game::Width; x += 30)
    {
        line.setPosition(x, 0);
        window.draw(line);
    }
}
