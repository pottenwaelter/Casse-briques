#include "Brick.h"
#include <iostream>

Brick::Brick()
{
	m_spriteHeight = 128;
	m_spriteWidth = 384;
	m_spriteScale = 0.4;
	m_xOffset = 0;
	m_yOffset = 130;
	loadTexture("ressources/Breakout_Tile_Free.png");
	m_brickWidth = m_spriteWidth * m_spriteScale;
	m_brickHeight = m_spriteHeight * m_spriteScale;
	m_healthPoints = 1;
}

Brick::Brick(int xOffset, int yOffset, int width, int height, float scale)
{
	m_spriteHeight = height;
	m_spriteWidth = width;
	m_spriteScale = scale;
	m_xOffset = xOffset;
	m_yOffset = yOffset;
	loadTexture("ressources/Breakout_Tile_Free.png");
	m_brickWidth = m_spriteWidth * m_spriteScale;
	m_brickHeight = m_spriteHeight * m_spriteScale;
	m_sprite.setOrigin(Vector2f(m_brickWidth, m_brickHeight));
	m_healthPoints = 1;
}

void Brick::loadTexture(std::string text)
{
	if (!m_texture.loadFromFile(text))
	{
		std::cout << "Erreur du chargement de la texture : " + text << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(IntRect(m_xOffset, m_yOffset, m_spriteWidth, m_spriteHeight));
	m_sprite.setScale(m_spriteScale, m_spriteScale);
}

int Brick::getHealthPoints()
{
	return m_healthPoints;
}

void Brick::brickGetsHit()
{
	m_healthPoints--;
}

void Brick::setBrickPosition(float xPos, float yPos)
{
	m_sprite.setPosition(xPos, yPos);
}

void Brick::setBrickHealthPoints(int hp)
{
	m_healthPoints = hp;
}

float Brick::getBrickHeight()
{
	return m_brickHeight;
}

float Brick::getBrickWidth()
{
	return m_brickWidth;
}

float Brick::getXPos()
{
	return m_sprite.getPosition().x;
}

float Brick::getYPos()
{
	return m_sprite.getPosition().y;
}

int Brick::getTextRect()
{
	return m_sprite.getTextureRect().top;
}

Vector2f Brick::getScale()
{
	return m_sprite.getScale();
}

Vector2f Brick::getOrigin()
{
	return m_sprite.getOrigin();
}

void Brick::getBrickPosition() const
{
	std::cout << "X : " << m_sprite.getPosition().x << ", Y : " << m_sprite.getPosition().y << std::endl;
}

FloatRect Brick::getHitbox()
{
	return m_sprite.getGlobalBounds();
}

Brick::~Brick()
{
	std::cout << "Destruction" << std::endl;
}

Player::Player() : Brick(1158, 462, 243, 64, 0.5)
{
	m_playerSpeed = 5;
	m_playerLives = 5;
}

void Player::movePlayer(std::string direction)
{
	if (direction == "right")
	{
		m_sprite.move(m_playerSpeed, 0);
	}

	if (direction == "left")
	{
		m_sprite.move(-m_playerSpeed, 0);
	}
}

float Player::getPlayerSpeed()
{
	return m_playerSpeed;
}

int Player::getPlayerLives()
{
	return m_playerLives;
}

void Player::playerLosesLife()
{
	m_playerLives--;
}