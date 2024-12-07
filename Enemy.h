#pragma once

#include <SFML/Graphics.hpp>

class Enemy
{
private:
	void initVariables();
	void initShape();

	sf::CircleShape _shape;
	unsigned _pointCount;
	float _speed;
	int _type;
	int _hp;
	int _hpMax;
	int _damage;
	int _points;

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	const sf::FloatRect getBounds() const;
	const unsigned& getPoints() const;
	const unsigned& getDamage() const;

	void update();
	void render(sf::RenderTarget* target);
};

