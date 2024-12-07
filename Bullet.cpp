#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dirX, float dirY, float movement_speed)
{
	this->_sprite.setTexture(*texture);
	this->_sprite.setPosition(pos_x, pos_y);
	this->_sprite.setScale(0.04f, 0.04f);

	this->_direction.x = dirX;
	this->_direction.y = dirY;
	this->_movementSpeed = movement_speed;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->_sprite.getGlobalBounds();
}

void Bullet::update()
{
	this->_sprite.move(this->_movementSpeed * this->_direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->_sprite);
}
