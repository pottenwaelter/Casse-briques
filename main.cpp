#include "main.h"

int main()
{
    window.setFramerateLimit(60);
    xSpacing = getBrickSpacing();
    //Placement des briques
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 6; i++)
        {
            /* 
            Pour les indices : on aura d'abord i = 0->1->2, etc avec j = 0, donc i + j * 6 aura toujours j = 0
            A la fin du premier passage sur les i, on sera à l'indice 5 et on reprend avec i = 0, donc i + j * 6 => 0 + 6 puisque j s'incrémente à 1
            Ce qui fait que ça boucle correctement et les blocs sont bien placés
            */
            bricks[i + j * 6].setBrickPosition((xSpacing + i * bricks[i].getBrickWidth()), (100 + j * bricks[i].getBrickHeight()));
        }
    }

    //Placement du joueur
    playerHeight = player.getBrickHeight();
    playerWidth = player.getBrickWidth();
    player.setBrickPosition(WIN_WIDTH / 2, WIN_HEIGHT - 30);

    //Initialisation et placement du sprite de la balle
    if (!ballTexture.loadFromFile("ressources/Breakout_Tile_Free.png"))
    {
        cout << "Erreur chargement texture balle" << endl;
    }
    ballSprite.setTexture(ballTexture);
    ballSprite.setTextureRect(IntRect(1403, 652, ballSpriteSize, ballSpriteSize));
    ballSprite.setScale(0.5, 0.5);
    ballSprite.setOrigin(ballSpriteSize / 2, ballSpriteSize / 2);
    ballSprite.setPosition(WIN_WIDTH / 2, player.getYPos() - playerHeight - 5);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            input.inputHandler(event, window);
        }

        checkInput();
        if (hasGameStarted)
        {
            ballMovement();
        }

        window.clear();
        for (int i = 0; i < bricks.size(); i++)
        {
                window.draw(bricks[i]); 
        }
        window.draw(player);
        window.draw(ballSprite);
        if (isBackspacePressed)
        {
            window.draw(ballRect);
        }
    
        window.display();
    }

    return 0;
}

void checkInput()
{
    if (player.getXPos() > playerWidth / 2) // si la raquette du joueur plus loin que le bord gauche de la fenêtre
    {
        if (input.getKey().left == true)
        {
            player.movePlayer("left");
            if (!hasGameStarted)
            {
                ballSprite.move(-playerSpeed, 0); // on l'autorise à aller vers la gauche
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
                ballSprite.move(playerSpeed, 0);
            }
        }
    }

    if (input.getKey().space == true) // on doit appuyer sur espace pour lancer la partie
    {
        hasGameStarted = true;
    }

    if (input.getKey().backspace == true)
    {
        isBackspacePressed = true;
    }
    else
    {
        isBackspacePressed = false;
    }

    if (input.getKey().escape == true)
    {
        window.close();
    }
}

float getBrickSpacing()
{
    float totalWidth = bricks[0].getBrickWidth() * 6; // largeur totale du rectangle de l'ensemble des briques
    float spacing = (WIN_WIDTH - totalWidth) / 2;

    return spacing;
}

void ballMovement()
{
    ballHitbox = ballSprite.getGlobalBounds();
    ballRect.setSize(Vector2f(ballSpriteSize / 2, ballSpriteSize / 2));
    ballRect.setPosition(ballHitbox.left, ballHitbox.top);
    ballRect.setFillColor(Color(255, 0, 0, 150));
    ballSprite.move(-xBallSpeed, -yBallSpeed);
    //Pour faire rebondir la balle sur les coins de l'écran, on multiplie la vitesse par -1 pour qu'elle reparte dans l'autre sens
    if (ballSprite.getPosition().x < 1 + ballSpriteSize / 4 || ballSprite.getPosition().x >= WIN_WIDTH - ballSpriteSize / 4)
    {
        xBallSpeed *= -1;
    }

    if (ballSprite.getPosition().y < 1 + ballSpriteSize / 4 || ballSprite.getPosition().y >= WIN_HEIGHT - ballSpriteSize / 4)
    {
        yBallSpeed *= -1;
    }

    collisionManagement();
}

void collisionManagement()
{
    //TODO : IMPROVE HITBOXES
    //Different behaviors if the ball hits the side or the corner of a brick
    //Direction changes according to where the ball hits the player racket
    /*if (ballHitbox.top >= bricks[23].getHitbox().top)
    {
        cout << "1" << endl;
    }
    else
    {
        cout << "0" << endl;
    }*/
    if (!hasCollided)
    {
        if (ballHitbox.intersects(player.getHitbox()))
        {
            yBallSpeed *= -1;
            hasCollided = true;
            collisionClock.restart();
        }

        for (int i = 0; i < bricks.size(); i++)
        {
            /* 
            si le côté gauche du sprite de la balle a un x inférieur ou égal au x du côté droit d'une brique (left + width) ET si les coordonnées y de la balle
            sont comprises entre les coordonnées y de la brique ET si la position x de la balle est supérieure à l'espace à gauche des briques
            -> la balle repart vers la droite       
            */
            if(ballHitbox.intersects(bricks[i].getHitbox()))
            {
                if (ballHitbox.left <= bricks[i].getHitbox().left + bricks[i].getHitbox().width
                    && ballHitbox.left > bricks[i].getHitbox().left + bricks[i].getBrickWidth() - 5
                    && ballHitbox.top + ballSpriteSize / 2 >= bricks[i].getHitbox().top 
                    && ballHitbox.top + ballSpriteSize / 2 <= bricks[i].getHitbox().top + bricks[i].getHitbox().height)
                {
                    xBallSpeed *= -1;
                    cout << "collision droite" << endl;
                    hasCollided = true;
                    collisionClock.restart();
                }
                else if (ballHitbox.left + ballHitbox.width >= bricks[i].getHitbox().left
                    && ballHitbox.left + ballHitbox.width < bricks[i].getHitbox().left + 5
                    && ballHitbox.top + ballSpriteSize / 2 >= bricks[i].getHitbox().top
                    && ballHitbox.top + ballSpriteSize / 2 <= bricks[i].getHitbox().top + bricks[i].getHitbox().height)
                {
                    xBallSpeed *= -1;
                    cout << "collision gauche" << endl;
                    hasCollided = true;
                    collisionClock.restart();
                }
                /*
                si le haut du sprite de la balle a un y inférieur ou égal au y du bas d'une brique (top + height) et si les coordonnées x de la balle sont comprises
                entre le x gauche et le x droit de la même brique -> la balle repart vers le bas
                */
                if (ballHitbox.top <= bricks[i].getHitbox().top + bricks[i].getHitbox().height
                    && ballHitbox.top > bricks[i].getHitbox().top + bricks[i].getHitbox().height - 5
                    && ballHitbox.left + ballSpriteSize / 2 >= bricks[i].getHitbox().left 
                    && ballHitbox.left + ballSpriteSize / 2 <= bricks[i].getHitbox().left + bricks[i].getHitbox().width)
                {
                    yBallSpeed *= -1;
                    cout << "collision bas" << endl;
                    hasCollided = true;
                    collisionClock.restart();
                }
                else if(ballHitbox.top + ballHitbox.height >= bricks[i].getHitbox().top
                    && ballHitbox.top + ballHitbox.height < bricks[i].getHitbox().top + 5
                    && ballHitbox.left + ballSpriteSize / 2 >= bricks[i].getHitbox().left
                    && ballHitbox.left + ballSpriteSize / 2 <= bricks[i].getHitbox().left + bricks[i].getHitbox().width)
                {
                    yBallSpeed *= -1;
                    cout << "collision haut" << endl;
                    hasCollided = true;
                    collisionClock.restart();
                }
            }
        }
    }

    if (collisionClock.getElapsedTime().asSeconds() > 0.2 && hasCollided)
    {
        hasCollided = false;
    }
}