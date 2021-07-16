#ifndef GAME_H 
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <sstream>

// TODO add sprites and main background
// TODO add list of score and save it 
// TODO add sound 
// TODO add window ico

class Game 
{
    sf::RenderWindow *window;
    sf::Event ev;
    bool showPlayAgain;

    sf::Font font;
    sf::Text uiText;
    sf::Text goText;
    sf::Text paText;

    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    unsigned points;
    int health;
    bool gameOver;
    sf::RectangleShape enemy;
    std::vector<sf::RectangleShape> enemies;
    
    sf::Vector2i mousePositionWin;
    sf::Vector2f mousePos;
    bool mouseHeld;

    void initEnemies();
    void initText();
    void initVars();
    void intWin();
    const bool isRunning() const;
    const bool isGameOver() const;
    void renderText(sf::RenderTarget&  target);
    void updateText();
    void spawnEnemy();
    void updateEnemies();
    void renderEnemies(sf::RenderTarget& target);
    void pollEvents();
    void updateMousePosWin();
    void initPlayAgain();
    public:
        Game();
        ~Game();
        bool resume();
        void update();
        void render();
};

#endif
