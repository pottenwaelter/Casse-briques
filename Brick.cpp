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
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(IntRect(m_xOffset, m_yOffset, m_spriteWidth, m_spriteHeight));
	m_sprite.setScale(m_spriteScale, m_spriteScale);
	m_brickWidth = m_spriteWidth * m_spriteScale;
	m_brickHeight = m_spriteHeight * m_spriteScale;
	m_sprite.setOrigin(Vector2f(m_brickWidth / 2, m_brickHeight / 2));
	m_healthPoints = 1;
}

void Brick::loadTexture(std::string text)
{
	if (!m_texture.loadFromFile(text))
	{
		std::cout << "Erreur du chargement de la texture : " + text << std::endl;
	}
}

int Brick::getHealthPoints()
{
	return m_healthPoints;
}

void Brick::brickGetsHit()
{
	m_healthPoints--;
}

void Brick::setBrickPosition(int xPos, int yPos)
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

Player::Player()
{
	m_spriteHeight = 64;
	m_spriteWidth = 243;
	m_spriteScale = 0.5;
	m_xOffset = 1158;
	m_yOffset = 462;
	loadTexture("ressources/Breakout_Tile_Free.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(IntRect(m_xOffset, m_yOffset, m_spriteWidth, m_spriteHeight));
	m_sprite.setScale(m_spriteScale, m_spriteScale);
	m_brickWidth = m_spriteWidth * m_spriteScale;
	m_brickHeight = m_spriteHeight * m_spriteScale;
	m_playerSpeed = 4;
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