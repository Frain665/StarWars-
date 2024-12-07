#include "Enemy.h"

void Enemy::initVariables()
{
	this->_pointCount = rand() % 8 + 3;
	this->_type = 0;
	this->_speed = static_cast<float>(this->_pointCount  / 2);
	this->_hpMax = static_cast<int>(this->_pointCount);
	this->_hp = _hpMax;
	this->_damage = this->_pointCount;
	this->_points = this->_pointCount;
	
}

void Enemy::initShape()
{
	this->_shape.setRadius(this->_pointCount * 3);
	this->_shape.setPointCount(this->_pointCount);
	this->_shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}


Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();

	this->initShape();

	this->_shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

const sf::FloatRect Enemy::getBounds() const
{
	return this->_shape.getGlobalBounds();
}

const unsigned& Enemy::getPoints() const
{
	return this->_points;
}

const unsigned& Enemy::getDamage() const
{
	return this->_damage;
}

void Enemy::update()
{
	this->_shape.move(0.f, this->_speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->_shape);
}
