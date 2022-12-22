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
float xBallSpeed = 3.5;
float yBallSpeed = 3.5;
float xSpacing;
int ballSpriteSize = 64;
bool hasGameStarted = false;
bool hasCollided = false;
bool isBackspacePressed = false;
bool isGameOver = false;
Clock collisionClock;
int brickColumn = 0;
int brickRow = 0;

//Variables de texte
InGameText levelText;
InGameText gameOverText;

//Instances d'objets
Texture spriteSheet;
Texture levelTexture;
Sprite levelSprite;
Sprite playerSprite;
Sprite ballSprite;
RectangleShape ballRect;
FloatRect ballHitbox;
list<Brick> bricks(24);
Player player;
vector<Sprite> heartSprites(player.getPlayerLives());
Input input;
RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Casse-briques");


//Prototypes de fonctions
void loadBaseTexture();
void setBall();
void setLevelBackground(string file);
void checkInput();
float getBrickSpacing();
void ballMovement();
void collisionManagement();
void setHearts();
void playerLifeLossManagement();
void centerText(Text text);
void prepareStartingTexts();