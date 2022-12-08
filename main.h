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

//Instances d'objets
CircleShape ball;
Brick bricks[24];
Player player(playerWidth, playerHeight);
Input input;
RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Casse-briques");



//Prototypes de fonctions
void checkInput();
float getBrickSpacing();