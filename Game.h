#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <sstream>
#include <sstream>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game
{
private:
	void initWindow();
	void initVariables();
	void initTextures();
	void initPlayer();
	void initEnemies();
	void initWorld();
	void initGUI();

	sf::RenderWindow* _window;
	sf::Event _event;
	sf::VideoMode _videoMode;

	std::map<std::string, sf::Texture*> _textures;
	std::vector<Bullet*> _bullets;

	Player* _player;

	sf::RectangleShape _playerHpBar;
	sf::RectangleShape _playerHpBarBack;

	sf::Font _font;

	sf::Text _pointText;
	sf::Text _gameOverText;

	unsigned _points;

	float _spawnEnemyTimer;
	float _spawnEnemyTimerMax;
	std::vector<Enemy*> _enemies;

	sf::Sprite _worldBackGround;
	sf::Texture _worldBackGroundTex;

public:
	Game();
	virtual ~Game();
	
	void run();

	void surveyOfClicks();
	void updateInput();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void updateCollision();
	void updateWorld();
	void updateGUI();
	void update();

	void render(sf::RenderTarget& target);
	void renderWorld();
	void renderGUI();
};

