#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Brick.h"
#include "Input.h"

using namespace std;
using namespace sf;

//Variables globales
Brick bricks[24];
Player player(150, 20);
Input input;
RenderWindow window(VideoMode(1200, 720), "Casse-briques");

//Prototypes de fonctions
void checkInput();