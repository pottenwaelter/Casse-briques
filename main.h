#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Brick.h"
#include "Input.h"

using namespace std;
using namespace sf;

//Constantes
const int WIN_WIDTH = 1200;
const int WIN_HEIGHT = 720;

//Variables globales
float playerWidth = 150;
float playerHeight = 20;
float xBallSpeed = 3.f;
float yBallSpeed = 3.f;
bool hasGameStarted = false;
bool checkPlayerHitbox = false;
bool hasCollided = false;
Clock collisionClock;

//Instances d'objets
CircleShape ball;
FloatRect ballHitbox;
Brick bricks[24];
Player player(playerWidth, playerHeight);
Input input;
RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Casse-briques");
//Préparation des hitboxes du joueur
RectangleShape playerRects[3];
FloatRect playerHitboxes[3];



//Prototypes de fonctions
void checkInput();
float getBrickSpacing();
void ballMovement();