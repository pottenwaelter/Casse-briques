#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class Brick : public Drawable
{
public:
	Brick();
	int getHealthPoints();
	void brickGetsHit();
	void setBrickPosition(int xPos, int yPos);
	void setBrickHealthPoints(int hp);
	float getBrickWidth();
	float getBrickHeight();
	float getXPos();
	float getYPos();
	FloatRect getHitbox();
	void getBrickPosition() const;
	~Brick();
protected: // en prévision de classe fille
	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		target.draw(m_brick, states);
	}
	int m_healthPoints;
	float m_brickWidth;
	float m_brickHeight;
	RectangleShape m_brick;
};

class Player : public Brick
{
public:
	Player(float width, float height);
	void movePlayer(std::string direction);

private:
	float m_playerSpeed;
};

#endif // !BRICK_H


