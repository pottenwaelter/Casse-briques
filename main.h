#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include "Brick.h"
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
Clock collisionClock;

//Instances d'objets
Texture playerTexture;
Sprite playerSprite;
Texture ballTexture;
Sprite ballSprite;
CircleShape ball;
RectangleShape ballRect;
FloatRect ballHitbox;
vector<Brick> bricks(24);
Player player;
Input input;
RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Casse-briques");



//Prototypes de fonctions
void checkInput();
float getBrickSpacing();
void ballMovement();
void collisionManagement();