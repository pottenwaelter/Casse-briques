#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include "Brick.h"
#include <list>
#include "Input.h"

using namespace std;
using namespace sf;

//Constantes
const int WIN_WIDTH = 1200;
const int WIN_HEIGHT = 720;

//Variables globales
float playerWidth;
float ballRadius = 12.f;
float playerHeight;
float xBallSpeed = 3.5;
float yBallSpeed = 3.5;
float playerSpeed = 4.f;
float xSpacing;
int ballSpriteSize = 64;
bool hasGameStarted = false;
bool hasCollided = false;
bool isBackspacePressed = false;
bool brickIFrame = false;
Clock iFrameClock;
Clock collisionClock;
int brickColumn = 0;
int brickRow = 0;

//Instances d'objets
Texture playerTexture;
Sprite playerSprite;
Texture ballTexture;
Sprite ballSprite;
CircleShape ball;
RectangleShape ballRect;
FloatRect ballHitbox;
list<Brick> bricks(24);
Player player;
Input input;
RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Casse-briques");

//Itérateur de liste
list<Brick>::iterator it2 = bricks.begin();



//Prototypes de fonctions
void checkInput();
float getBrickSpacing();
void ballMovement();
void collisionManagement();