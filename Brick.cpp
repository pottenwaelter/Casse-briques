#include "Brick.h"
#include <iostream>

Brick::Brick()
{
	m_brickWidth = 150;
	m_brickHeight = 30;
	m_brick.setSize(Vector2f(m_brickWidth, m_brickHeight));
	m_brick.setFillColor(Color(175, 175, 175));
	m_brick.setOutlineThickness(2);
	m_brick.setOutlineColor(Color(75, 75, 75));
	m_healthPoints = 1;
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
	m_brick.setPosition(xPos, yPos);
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

void Brick::getBrickPosition() const
{
	std::cout << "X : " << m_brick.getPosition().x << ", Y : " << m_brick.getPosition().y << std::endl;
	std::cout << m_brick.getGlobalBounds().top << std::endl;
}