#include "Game.h"
#include "MenuScreen.h"
#include "SettingsScreen.h"
#include <cmath>
#include <iostream>

using namespace sfSnake;

// 初始化静态成员变量
std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();
std::shared_ptr<SettingsScreen> settingsScreen = std::make_shared<SettingsScreen>();
sf::Music Game::backgroundMusic_;

// 定义颜色常量
const sf::Color Game::Color::Yellow = sf::Color(0xf1c40fff);
const sf::Color Game::Color::Green = sf::Color(0x2ecc71ff);
const sf::Color Game::Color::Background[] = {
    sf::Color(0xeaeaeaee), // White
    sf::Color(0x747474ff), // Black
    sf::Color(0x9f6133aa)  // Brown
};
const sf::Color Game::Color::Grid[] = {
    sf::Color(0xfbfbfbaa), // White
    sf::Color(0x31313116), // Black
    sf::Color(0x5a351d16)  // Brown
};
const sf::Color Game::Color::NotSeleted = sf::Color(0x00000055);
const sf::Color Game::Color::Fruit[] = {
    sf::Color(0x212f3dff), // Black
    sf::Color(0x935116ff), // Brown
    sf::Color(0xe74c3cff), // Red
    sf::Color(0x5dade2ff), // Blue
    sf::Color(0x2ecc71ff)  // Green
};

// 初始化视频模式
sf::VideoMode Game::initVideoMode_()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    return sf::VideoMode(
        desktopMode.width / 2.0f,
        desktopMode.height / 2.0f,
        desktopMode.bitsPerPixel);
}

// 定义全局视频模式
sf::VideoMode Game::GlobalVideoMode = Game::initVideoMode_();

// 播放背景音乐
void Game::playbackgroundmusic(const std::string& filename)
{
    if (!backgroundMusic_.openFromFile(filename))
    {
        std::cerr << "Error loading background music from " << filename << std::endl;
    }
    else
    {
        backgroundMusic_.setLoop(true);  // 设置循环播放
        backgroundMusic_.play();
    }
}

// 游戏启动函数
void Game::start()
{
    // 创建窗口
    sf::RenderWindow window(sf::VideoMode(Game::Width, Game::Height), "Snake Game");
    // 播放背景音乐
    playbackgroundmusic("../Music/bg_music.wav");

    // 创建时钟
    sf::Clock clock;
    // 游戏主循环
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart(); // 获取时间间隔
        sf::Event event;
        // 处理窗口事件
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 处理输入、更新状态、渲染屏幕
        Screen->handleInput(window);
        Screen->update(deltaTime);

        window.clear(sf::Color::White);
        Screen->render(window);
        window.display();
    }
}
