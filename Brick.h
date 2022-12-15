#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class Brick : public Drawable
{
public:
	Brick();
	Brick(int xOffset, int yOffset, int width, int height, float scale);
	void loadTexture(std::string text);
	int getHealthPoints();
	void brickGetsHit();
	void setBrickPosition(float xPos, float yPos);
	void setBrickHealthPoints(int hp);
	float getBrickWidth();
	float getBrickHeight();
	float getXPos();
	float getYPos();
	Vector2f getScale();
	Vector2f getOrigin();
	FloatRect getHitbox();
	void getBrickPosition() const;
	~Brick();
protected: // en prévision de classe fille
	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		target.draw(m_sprite, states);
	}
	int m_healthPoints;
	int m_spriteWidth;
	int m_spriteHeight;
	int m_xOffset;
	int m_yOffset;
	float m_spriteScale;
	float m_brickWidth;
	float m_brickHeight;
	Texture m_texture;
	Sprite m_sprite;
};

class Player : public Brick
{
public:
	Player();
	void movePlayer(std::string direction);

private:
	float m_playerSpeed;
};

#endif // !BRICK_H


