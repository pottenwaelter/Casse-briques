#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include "Brick.h"
#include <list>
#include "Input.h"
#include "Textes.h"

using namespace std;
using namespace sf;

//Constantes
const int WIN_WIDTH = 1200;
const int WIN_HEIGHT = 720;

//Variables globales
float playerWidth;
float ballRadius = 12.f;
float playerHeight;
float xBallSpeed = 4.f;
float yBallSpeed = 4.f;
float xSpacing;
int numberOfBricks = 24;
int ballSpriteSize = 64;
bool hasGameStarted = false;
bool hasCollided = false;
bool isGameOver = false;
bool isTextDisplayed = false;
int brickColumn = 0;
int brickRow = 0;
int currentLevel = 1;

//Offsets de sprite des niveux
Vector2i level1Offsets(0, 130);
Vector2i level2Offsets(772, 390);

//Timers
Clock collisionClock;
Clock blinkingClock;

//Variables de texte
InGameText levelText;
InGameText gameOverText;
InGameText restartText;

//Instances d'objets
Texture spriteSheet;
Texture levelTexture;
Sprite levelSprite;
Sprite playerSprite;
Sprite ballSprite;
RectangleShape ballRect;
FloatRect ballHitbox;
list<Brick> bricks(numberOfBricks);
Player player;
vector<Sprite> heartSprites(player.getPlayerLives());
Input input;
RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Casse-briques");


//Prototypes de fonctions
void loadBaseTexture();
void setPlayer();
void setBall();
void setLevelBackground(string file);
void checkInput();
float getBrickSpacing();
void ballMovement();
void collisionManagement();
void setHearts();
void playerLifeLossManagement();
void prepareStartingTexts();
void restartGame();
void setLevel1();
void setLevel2();