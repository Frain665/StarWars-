#include "Game.h"

void Game::initWindow()
{
	this->_videoMode.height = 600;
	this->_videoMode.width = 800;
	this->_window = new sf::RenderWindow(this->_videoMode,
		"Swaglords of space", sf::Style::Close | sf::Style::Titlebar);
	this->_window->setFramerateLimit(60);
	this->_window->setVerticalSyncEnabled(false);
}

void Game::initVariables()
{
	this->_window = nullptr;
	this->_points = 0;
}

void Game::initTextures()
{
	this->_textures["BULLET"] = new sf::Texture();
	this->_textures["BULLET"]->loadFromFile("Textures/bullet.png");
}

void Game::initPlayer()
{
	this->_player = new Player();
}

void Game::initEnemies()
{
	this->_spawnEnemyTimerMax = 50.f;
	this->_spawnEnemyTimer = _spawnEnemyTimerMax;
}

void Game::initWorld()
{
	if (!this->_worldBackGroundTex.loadFromFile("Textures/space.png"))
	{
		std::cerr << "Error::_worldBackGroundTex.loadFromFile: Failed to load this file!" << std::endl;
	}

	this->_worldBackGround.setTexture(this->_worldBackGroundTex);
}

void Game::initGUI()
{
	if (!this->_font.loadFromFile("Fonts/font.ttf"))
	{
		std::cerr << "Error::_font.loadFromFile: Failed to load file!" << std::endl;
	}

	this->_pointText.setFont(this->_font);
	this->_pointText.setCharacterSize(34);
	this->_pointText.setFillColor(sf::Color::White);
	this->_pointText.setString("NONE"); 

	this->_gameOverText.setFont(this->_font);
	this->_gameOverText.setCharacterSize(60);
	this->_gameOverText.setFillColor(sf::Color::Red);
	this->_gameOverText.setString("Game over!");
	this->_gameOverText.setPosition(this->_window->getSize().x / 2 - this->_gameOverText.getGlobalBounds().width / 2, 
									this->_window->getSize().y / 2 - this->_gameOverText.getGlobalBounds().height / 2);

	this->_playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->_playerHpBar.setFillColor(sf::Color::Red);
	this->_playerHpBar.setPosition(sf::Vector2f(this->_window->getSize().x - 350.f, 25.f));

	this->_playerHpBarBack = this->_playerHpBar;
	this->_playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));


}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initGUI();
	this->initTextures();
	this->initWorld();
	this->initPlayer();
	this->initEnemies();
}

Game::~Game()
{
	delete this->_window;
	delete this->_player;

	for (auto& e : this->_textures)
	{
		delete e.second;
	}

	for (auto* e : this->_bullets)
	{
		delete e;
	}

	for (auto* e : this->_enemies)
	{
		delete e;
	}
}

void Game::run()
{
	while (this->_window->isOpen())
	{
		this->surveyOfClicks();
		
		if (this->_player->getHp() > 0)
		{
			this->update();
		}
		
		this->render(*this->_window);
	}
}

void Game::surveyOfClicks()
{
	while (this->_window->pollEvent(this->_event))
	{
		switch (this->_event.type)
		{
		case sf::Event::Closed:
			this->_window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->_event.key.code == sf::Keyboard::Escape)
				this->_window->close();
			break;
		default:
			break;
		}
	}
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->_player->movePlayer(-0.1f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->_player->movePlayer(0.1f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->_player->movePlayer(0.f, -0.1f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->_player->movePlayer(0.f, 0.1f);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->_player->canAttack())
	{
		this->_bullets.push_back(new Bullet(this->_textures["BULLET"],
			this->_player->getPos().x + this->_player->getBounds().width / 2.3f,
			this->_player->getPos().y, 0.f, -1.f, 5.f));
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->_bullets)
	{
		bullet->update();

		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			delete this->_bullets.at(counter);
			this->_bullets.erase(this->_bullets.begin() + counter);
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	this->_spawnEnemyTimer += 0.5f;

	if (this->_spawnEnemyTimer >= _spawnEnemyTimerMax)
	{
		this->_enemies.push_back(new Enemy(rand() % this->_window->getSize().x - 20.f, -100.f));
		_spawnEnemyTimer = 0.f;
	}

	unsigned counter = 0;
	for (auto* enemy : this->_enemies)
	{
		enemy->update();

		if (enemy->getBounds().top > this->_window->getSize().y)
		{
			delete this->_enemies.at(counter);
			this->_enemies.erase(this->_enemies.begin() + counter);
		}
		else if(enemy->getBounds().intersects(this->_player->getBounds()))
		{
			this->_player->loseHp(this->_enemies.at(counter)->getPoints());
			delete this->_enemies.at(counter);
			this->_enemies.erase(this->_enemies.begin() + counter);
		}

		++counter;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->_enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->_bullets.size() && !enemy_deleted; k++)
		{
			if(this->_enemies[i]->getBounds().intersects(this->_bullets[k]->getBounds()))
			{
				this->_points += this->_enemies[i]->getPoints();

				delete this->_enemies[i];
				this->_enemies.erase(this->_enemies.begin() + i);

				delete this->_bullets[k];
				this->_bullets.erase(this->_bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::updateCollision()
{
	//Left 
	if (this->_player->getBounds().left < 0.f)
	{
		this->_player->setPosition(0.f, this->_player->getBounds().top);
	}

	//Right
	else if (this->_player->getBounds().left + this->_player->getBounds().width 
	> this->_window->getSize().x)
	{
		this->_player->setPosition(this->_window->getSize().x - this->_player->getBounds().width, this->_player->getBounds().top);
		
	}

	//Down
	if (this->_player->getBounds().height > this->_window->getSize().y - this->_player->getBounds().top)
	{
		this->_player->setPosition(this->_player->getBounds().left, this->_window->getSize().y - this->_player->getBounds().height);
	}

	//Top
	else if (this->_player->getBounds().top < 0.f)
	{
		this->_player->setPosition(this->_player->getBounds().left, 0.f);
	}

}

void Game::updateWorld()
{

}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points: " << this->_points;
	this->_pointText.setString(ss.str());

	//this->_player->setHp(9);
	float hpPercent = static_cast<float>(this->_player->getHp()) / this->_player->getHpMax();
	this->_playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->_playerHpBar.getSize().y));
}

void Game::update()
{

	this->updateInput();

	this->_player->update();

	this->updateCollision();

	this->updateWorld();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();
}

void Game::render(sf::RenderTarget& target)
{
	this->_window->clear();

	this->renderWorld();

	this->_player->render(*this->_window);

	for (auto* bullet : this->_bullets)
	{
		bullet->render(this->_window);
	}

	for (auto* enemy : this->_enemies)
	{
		enemy->render(this->_window);
	}

	this->renderGUI();

	if (this->_player->getHp() <= 0)
	{
		this->_window->draw(this->_gameOverText);
	}

	this->_window->display();
}

void Game::renderWorld()
{
	this->_window->draw(this->_worldBackGround);
}

void Game::renderGUI()
{
	this->_window->draw(this->_pointText);
	this->_window->draw(this->_playerHpBarBack);
	this->_window->draw(this->_playerHpBar);
}
