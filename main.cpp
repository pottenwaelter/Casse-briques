#include "main.h"

int main()
{
    window.setFramerateLimit(60);
    xSpacing = getBrickSpacing();
    //Placement des briques
    setLevel();
    //Chargement des textures (sprite sheet)
    loadBaseTexture();

    //Chargement du background du niveau
    setLevelBackground("ressources/backgrounds/sunset.jpg");

    //Placement du joueur
    setPlayer();
    //Initialisation et placement du sprite de la balle
    setBall();
    //Initialisation des coeurs de vie
    setHearts();

    //Initialisation des textes 
    prepareStartingTexts();

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            input.inputHandler(event, window);
        }

        //Centrage des textes
        levelText.centerTextOrigin();
        gameOverText.centerTextOrigin();
        restartText.centerTextOrigin();

        if (heartSprites.empty())
        {
            isGameOver = true;
        }

        //Gestion du mouvement de la balle
        if (hasGameStarted)
        {
            ballMovement();
        }

        window.clear(Color::White);
        //Affichage de tous les éléments du jeu
        window.draw(levelSprite);
        
        for (auto it = bricks.begin(); it != bricks.end(); it++)
        {
            Brick& brick = (*it);
            window.draw(brick);
        }
        window.draw(player);
        window.draw(ballSprite);
        for (int i = 0; i < heartSprites.size(); i++)
        {
            window.draw(heartSprites[i]);
        }
        window.draw(levelText);
        if (isGameOver)
        {
            window.draw(gameOverText);
            if (!isTextDisplayed)
            {
                blinkingClock.restart();
                isTextDisplayed = true;
            }
            if (blinkingClock.getElapsedTime().asSeconds() > 0.7)
            {
                window.draw(restartText);
            }
            if (blinkingClock.getElapsedTime().asSeconds() > 1.4)
            {
                isTextDisplayed = false;
            }
        }
        //gestion des inputs
        checkInput();
    
        window.display();
    }

    return 0;
}

void loadBaseTexture()
{
    if (!spriteSheet.loadFromFile("ressources/Breakout_Tile_Free.png"))
    {
        cout << "Erreur chargement texture" << endl;
    }
}

void setBall()
{
    ballSprite.setTexture(spriteSheet);
    ballSprite.setTextureRect(IntRect(1403, 652, ballSpriteSize, ballSpriteSize));
    ballSprite.setScale(0.5, 0.5);
    ballSprite.setOrigin(ballSpriteSize / 2, ballSpriteSize / 2);
    ballSprite.setColor(Color(200, 50, 50));
    ballSprite.setPosition(player.getXPos(), player.getYPos() - playerHeight - 5);
}

void setPlayer()
{
    playerHeight = player.getBrickHeight();
    playerWidth = player.getBrickWidth();
    player.setBrickPosition(WIN_WIDTH / 2, WIN_HEIGHT - 30);
}

void checkInput()
{
    if (!isGameOver)
    {
        if (player.getXPos() > playerWidth / 2) // si la raquette du joueur plus loin que le bord gauche de la fenêtre
        {
            if (input.getKey().left == true)
            {
                player.movePlayer("left");
                if (!hasGameStarted)
                {
                    ballSprite.move(-(player.getPlayerSpeed()), 0); // on l'autorise à aller vers la gauche
                }
            }
        }

        if (player.getXPos() < WIN_WIDTH - playerWidth / 2) // pareil pour la droite
        {
            if (input.getKey().right == true)
            {
                player.movePlayer("right");
                if (!hasGameStarted)
                {
                    ballSprite.move(player.getPlayerSpeed(), 0);
                }
            }
        }

        if (input.getKey().space == true) // on doit appuyer sur espace pour lancer la partie
        {
            hasGameStarted = true;
        }
    }

    if (isGameOver)
    {
        if (input.getKey().start == true)
        {
            restartGame();
        }
    }
    

    if (input.getKey().backspace == true)
    {
        window.draw(ballRect);
    }

    if (input.getKey().escape == true)
    {
        window.close();
    }
}

float getBrickSpacing()
{
    auto accessor = bricks.begin();
    float totalWidth = accessor->getBrickWidth() * 6; // largeur totale du rectangle de l'ensemble des briques
    float spacing = (WIN_WIDTH - totalWidth) / 2;

    return spacing;
}

void ballMovement()
{
    ballHitbox = ballSprite.getGlobalBounds();
   /* ballRect.setSize(Vector2f(ballSpriteSize / 2, ballSpriteSize / 2));
    ballRect.setPosition(ballHitbox.left, ballHitbox.top);
    ballRect.setFillColor(Color(255, 0, 0, 150));*/
    ballSprite.move(xBallSpeed, -yBallSpeed);
    //Pour faire rebondir la balle sur les coins de l'écran, on multiplie la vitesse par -1 pour qu'elle reparte dans l'autre sens
    if (ballSprite.getPosition().x < 1 + ballSpriteSize / 4 || ballSprite.getPosition().x >= WIN_WIDTH - ballSpriteSize / 4)
    {
        xBallSpeed *= -1;
    }

    if (ballSprite.getPosition().y < 1 + ballSpriteSize / 4)
    {
        yBallSpeed *= -1;
    }

    if (ballSprite.getPosition().y >= WIN_HEIGHT)
    {
        if (!isGameOver)
        {
            ballSprite.setPosition(player.getXPos(), player.getYPos() - playerHeight - 5);
            yBallSpeed *= -1;
        }
        playerLifeLossManagement();
        hasGameStarted = false;
    }

    collisionManagement();
}

void collisionManagement()
{
    //TODO : améliorer les hitboxes
    if (!hasCollided)
    {
        if (ballHitbox.intersects(player.getHitbox()))
        {
            if (ballHitbox.left > player.getHitbox().left + player.getHitbox().width - 50) // si la balle tape sur le côté droit de la raquette
            {
                if (xBallSpeed < 0)
                {
                    xBallSpeed *= -1; //la balle repart vers la droite
                }
            }

            if (ballHitbox.left + ballHitbox.width < player.getHitbox().left + 50) // si la balle tape sur le côté gauche de la raquette
            {
                if (xBallSpeed > 0)
                {
                    xBallSpeed *= -1; //la balle repart vers la gauche
                }
            }

            if (ballHitbox.top < player.getHitbox().top + player.getHitbox().height)
            {
                yBallSpeed *= -1;
            }
            hasCollided = true;
            collisionClock.restart();
        }
    }
       
    bool isYBrickCollision = false;
    bool isXBrickCollision = false;
    for (auto it = bricks.begin(); it != bricks.end();)
    {
        if (ballHitbox.intersects(it->getHitbox()))
        {               
            //On voit à quel point la balle a une intersection avec la brique dans chaque direction
            float leftOverlap = ballHitbox.left + ballHitbox.width - it->getHitbox().left;
            float rightOverlap = it->getHitbox().left + it->getHitbox().width - ballHitbox.left;
            float topOverlap = ballHitbox.top + ballHitbox.height - it->getHitbox().top;
            float bottomOverlap = it->getHitbox().top + it->getHitbox().height - ballHitbox.top;

            //Si le chevauchement gauche est plus petit que le chevauchement droit on peut dire que la balle a tapé la brique sur la gauche
            //inversement pour la droite
            bool leftCollision(abs(leftOverlap) < abs(rightOverlap));
            bool rightCollision(abs(rightOverlap) < abs(leftOverlap));
            //Pareil pour la collision haut/bas
            bool topCollision(abs(topOverlap) < abs(bottomOverlap));
            bool bottomCollision(abs(bottomOverlap) < abs(topOverlap));

            //Stockage du chevauchement minimal sur les axes X et Y
            float minXOverlap{ leftCollision ? leftOverlap : rightOverlap };
            float minYOverlap{ topCollision ? topOverlap : bottomOverlap };

            //Puis on change la direction de la balle en suivant ces règles
            if (abs(minXOverlap) < abs(minYOverlap))
            {
                if (leftCollision || rightCollision)
                {
                    //xBallSpeed *= -1;
                    isXBrickCollision = true;

                }
            }
            else
            {
                if (topCollision || bottomCollision)
                {
                    //yBallSpeed *= -1;
                    isYBrickCollision = true;
                }
            }

            it->brickGetsHit();
            if (it->getHealthPoints() == 0)
            {
                it = bricks.erase(it);
            }
        }
        else
        {
            it++;
        }
    }

    if (isXBrickCollision)
    {
        xBallSpeed *= -1;
    }
    if (isYBrickCollision)
    {
        yBallSpeed *= -1;
    }

    if (collisionClock.getElapsedTime().asSeconds() > 0.3 && hasCollided)
    {
        hasCollided = false;
    }
}

void setHearts()
{
    for (int i = 0; i < player.getPlayerLives(); i++)
    {
        heartSprites[i].setTexture(spriteSheet);
        heartSprites[i].setTextureRect(IntRect(1637, 652, 64, 58));
        heartSprites[i].setScale(0.5, 0.5);
        heartSprites[i].setColor(Color(255, 0, 0, 175));
        heartSprites[i].setPosition(i * 35 + 10, 10);
    }
}

void playerLifeLossManagement()
{
    if (!heartSprites.empty())
    {
        player.playerLosesLife();
        heartSprites.pop_back();
    }
}

void setLevelBackground(string file)
{
    if (!levelTexture.loadFromFile(file))
    {
        cerr << "Erreur chargement texture du background du niveau" << endl;
    }
    levelSprite.setTexture(levelTexture);
    levelSprite.setTextureRect(IntRect(0, 0, WIN_WIDTH, WIN_HEIGHT));
    levelSprite.setPosition(0, 0);
}

void prepareStartingTexts()
{
    levelText.setCharSize(25);
    levelText.setString("LEVEL 1");
    levelText.setPosition(WIN_WIDTH / 2, 20);

    gameOverText.setCharSize(40);
    gameOverText.setString("GAME OVER");
    gameOverText.setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);

    restartText.setCharSize(30);
    restartText.setString("PRESS ENTER TO RESTART THE GAME");
    restartText.setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2 + 50);
}


void restartGame()
{
    setPlayer();
    setBall();
    player.setPlayerLives(3);
    heartSprites.resize(player.getPlayerLives());
    setHearts();
    bricks.clear();
    bricks.resize(24);
    setLevel();
    isGameOver = false;
}

void setLevel()
{
    for (auto it = bricks.begin(); it != bricks.end(); ++it)
    {
        if (brickColumn < 6)
        {
            it->setBrickPosition(xSpacing + brickColumn * it->getBrickWidth(), 100 + brickRow * it->getBrickHeight());
            brickColumn++;
        }
        if (brickColumn == 6)
        {
            brickColumn = 0;
            brickRow++;
        }
    }
    brickColumn = brickRow = 0;
}