#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>

class Bullet
{
private:
	sf::Sprite _sprite;

	sf::Vector2f _direction;
	float _movementSpeed;


public:
	Bullet();
	Bullet(sf::Texture* texture,float pos_x, float pos_y,
		float dirX, float dirY, float movement_speed);
	virtual ~Bullet();

	const sf::FloatRect getBounds() const;
	
	void update();
	void render(sf::RenderTarget* target);
};

