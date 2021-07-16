#include "Game.h"
#include <SFML/Graphics/Color.hpp>

Game::Game() {
    initVars();
    intWin();
    initEnemies();
    initText();
    initPlayAgain();
}

Game::~Game() { delete window; }

const bool Game::isGameOver() const {
    return gameOver;
}

void Game::updateText() {
    std::stringstream ss;
    ss << "Score: " << points << '\n'
    << "heaalths: " << health;
    uiText.setString(ss.str());
}

void Game::spawnEnemy() {
    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)), 0.f);

    // randomize enemies
    int rnd = rand() % 5;
    switch (rnd) {
        case 0:
            enemy.setSize(sf::Vector2f(15.f, 15.f));
            enemy.setFillColor(sf::Color::Magenta);
            break;
        case 1:
            enemy.setSize(sf::Vector2f(20.f, 20.f));
            enemy.setFillColor(sf::Color::Red);
            break;
        case 2:
            enemy.setSize(sf::Vector2f(30.f, 30.f));
            enemy.setFillColor(sf::Color::Yellow);
            break;
        case 3:
            enemy.setSize(sf::Vector2f(40.f, 40.f));
            enemy.setFillColor(sf::Color::Cyan);
            break;
        case 4:
            enemy.setSize(sf::Vector2f(50.f, 50.f));
            enemy.setFillColor(sf::Color::Blue);
            break;
        default:
            enemy.setSize(sf::Vector2f(50.f, 50.f));
            enemy.setFillColor(sf::Color::Green);
            break;
    }
    enemies.push_back(enemy);
}
void Game::updateEnemies() {
    float speed = 1.f;
    if(points > 100) speed = 1.f;
    if(points > 300) speed = 2.f;
    if(points > 1000) speed = 3.f;
    if(points > 3000) speed = 4.f;

    if (enemies.size() < maxEnemies) {
        if (enemySpawnTimer >= enemySpawnTimerMax) {
            spawnEnemy();
            enemySpawnTimer = 0.f;
        } else {
            enemySpawnTimer += 1.f;
        }
    }

    for (int i = 0; i < enemies.size(); ++i) {
        enemies[i].move(0.f, speed);
        if(enemies[i].getPosition().y > window->getSize().y) {
            enemies.erase(enemies.begin() + i);
            --health;
        }
    }
    
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // this not allow to kill all enemy helding the mouse button
        if(mouseHeld == false) {
            mouseHeld = true;
            // one click -> one time loop starts -> one delete will be doneby frame
            bool deleted = false;
            for (int i = 0; i < enemies.size() && deleted == false; ++i) {
                if(enemies[i].getGlobalBounds().contains(mousePos)) {
                    if(enemies[i].getFillColor() == sf::Color::Magenta) points += 100;
                    if(enemies[i].getFillColor() == sf::Color::Red) points += 50;
                    if(enemies[i].getFillColor() == sf::Color::Yellow) points += 30;
                    if(enemies[i].getFillColor() == sf::Color::Cyan) points += 20;
                    if(enemies[i].getFillColor() == sf::Color::Blue) points += 10;
                    if(enemies[i].getFillColor() == sf::Color::Green) points += 5;
                    enemies.erase(enemies.begin() + i);
                    deleted = true;
                    points += 10;
                }
            }
        } 
    } else {
        mouseHeld = false;
    }
}

void Game::renderEnemies(sf::RenderTarget& target) {
    for (auto& e : enemies) {
        target.draw(e); 
    }
}

void Game::renderText(sf::RenderTarget& target) {
    target.draw(uiText);
}

void Game::pollEvents() {
    while(window->pollEvent(ev)) {
        if(ev.type == sf::Event::Closed) {
                window->close();
        }
    }
}

void Game::update() {
    pollEvents();
    if(!gameOver) {
        updateText();
        updateMousePosWin();
        updateEnemies();
    } else {
        showPlayAgain = true;
    }

    if(health <=0) gameOver = true;
}


void Game::initPlayAgain() {
    goText.setFillColor(sf::Color::Red);
    goText.setCharacterSize(50);
    goText.setFont(font);
    goText.setString("GAME OVER");
    goText.setPosition(250.f, 200.f);

    paText.setFillColor(sf::Color::White);
    paText.setCharacterSize(20);
    paText.setFont(font);
    paText.setString("Play again? (y/n)");
    paText.setPosition(290.f, 260.f);

}

void Game::render() {
    window->clear();
    renderText(*window);
    renderEnemies(*window);
    if(showPlayAgain) {
        window->draw(goText);
        window->draw(paText);
    }
    window->display();
}

void Game::updateMousePosWin() {
    mousePositionWin = sf::Mouse::getPosition(*window);
    mousePos = window->mapPixelToCoords(mousePositionWin);
}

void Game::initText() {
    uiText.setFillColor(sf::Color::White);
    uiText.setFont(font);
    uiText.setCharacterSize(12);
    uiText.setString("Score:");
}

void Game::initVars() {
    gameOver = false;
    health = 3;
    window = nullptr;
    enemySpawnTimerMax = 50.f;
    enemySpawnTimer = enemySpawnTimerMax;
    maxEnemies = 10;
    points = 0;
    mouseHeld = false;
    showPlayAgain = false;

    font.loadFromFile("JetBrains Mono Extra Bold Nerd Font Complete.ttf");
}

void Game::intWin() {
    window = new sf::RenderWindow(sf::VideoMode(800,600), "Falling asteroids");
    window->setFramerateLimit(60);
}

void Game::initEnemies() {
    enemy.setPosition(sf::Vector2f(10.f, 10.f));
    enemy.setSize(sf::Vector2f(50.f, 50.f));
    enemy.setFillColor(sf::Color(104, 58, 8));
    enemy.setOutlineColor(sf::Color::Green);
    enemy.setOutlineThickness(1.f);
}

bool Game::resume() {
    if(showPlayAgain) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            points = 0;
            health = 30;
            enemies.clear();
            showPlayAgain = false;
            gameOver = false;
            return false;
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
            return true;
        }
    }
    return false;
}
