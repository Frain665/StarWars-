#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

class Player
{
private:
	void initSprite();
	void initTexture();
	void initVariables();

	float _movementSpeed;
	
	float _attackCoolDown;
	float _attackCoolDownMax;

	int _hp;
	int _hpMax;

	sf::Sprite _sprite;
	sf::Texture _texture;

public:
	Player();
	virtual ~Player();

	void movePlayer(const float dirX, const float dirY);

	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;
	void setHp(const int hp);
	void loseHp(const int value);

	void setPosition(const sf::Vector2f pos);
	void setPosition(const float pos_x, const float pos_y);

	const bool canAttack();

	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};

