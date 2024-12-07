#include "Player.h"

void Player::initSprite()
{
	this->_sprite.setTexture(this->_texture);
	this->_sprite.setScale(1.f, 1.f);
}

void Player::initTexture()
{
	if (!this->_texture.loadFromFile("Textures/ship.png"))
	{
		std::cerr << "The file could not be uploaded!" << std::endl;
	}
}

void Player::initVariables()
{
	this->_movementSpeed = 100.f;

	this->_attackCoolDownMax = 10.f;
	this->_attackCoolDown = _attackCoolDownMax;

	this->_hpMax = 100;
	this->_hp = this->_hpMax;
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
}

void Player::movePlayer(const float dirX, const float dirY)
{
	this->_sprite.move(this->_movementSpeed * dirX,
		this->_movementSpeed * dirY);
}

const sf::Vector2f& Player::getPos() const
{
	return this->_sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->_sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->_hp;
}

const int& Player::getHpMax() const
{
	return this->_hpMax;
}

void Player::setHp(const int hp)
{
	this->_hp = hp;
}

void Player::loseHp(const int value)
{
	this->_hp -= value;
	if (this->_hp < 0)
		this->_hp = 0;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->_sprite.setPosition(pos.x, pos.y);
}

void Player::setPosition(const float pos_x, const float pos_y)
{
	this->_sprite.setPosition(pos_x, pos_y);
}

const bool Player::canAttack()
{
	if (this->_attackCoolDown >= this->_attackCoolDownMax)
	{
		this->_attackCoolDown = 0.f;
		return true;
	}

	return false;
}

void Player::updateAttack()
{
	if (this->_attackCoolDown < this->_attackCoolDownMax)
		this->_attackCoolDown += 0.5f;
}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->_sprite);
}
