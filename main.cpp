#include "main.h"

int main()
{
    window.setFramerateLimit(60);
    float xSpacing = getBrickSpacing();
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

    cout << "\n" << xSpacing + 0 * bricks[0].getBrickWidth() << endl;

    //Initialisation et placement de la balle
    ball.setFillColor(Color::Green);
    ball.setOutlineThickness(1);
    ball.setOutlineColor(Color::White);
    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius, ballRadius);
    ball.setPosition(WIN_WIDTH / 2, player.getYPos() - playerHeight - ballRadius / 2 - 2);

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
        window.draw(ball);
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
    if (player.getXPos() > playerWidth / 2)
    {
        if (input.getKey().left == true)
        {
            player.movePlayer("left");
            if (!hasGameStarted)
            {
                ball.move(-playerSpeed, 0);
            }
        }
    }

    if (player.getXPos() < WIN_WIDTH - playerWidth / 2)
    {
        if (input.getKey().right == true)
        {
            player.movePlayer("right");
            if (!hasGameStarted)
            {
                ball.move(playerSpeed, 0);
            }
        }
    }

    if (input.getKey().space == true)
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
    cout << "Largeur de toutes les briques : " << totalWidth << endl;
    cout << "Espace gauche et droite : " << spacing << endl;
    cout << "Largeur de la fenêtre : " << totalWidth + spacing * 2;

    return spacing;
}

void ballMovement()
{
    ballHitbox = ball.getGlobalBounds();
    ballRect.setSize(Vector2f(ballRadius * 2, ballRadius * 2));
    ballRect.setPosition(ballHitbox.left, ballHitbox.top);
    ballRect.setFillColor(Color(255, 0, 0, 150));
    ball.move(xBallSpeed, -yBallSpeed);
    if (ball.getPosition().x < 1 + ballRadius || ball.getPosition().x >= WIN_WIDTH - ballRadius)
    {
        xBallSpeed *= -1;
    }

    if (ball.getPosition().y < 1 + ballRadius || ball.getPosition().y >= WIN_HEIGHT - ballRadius)
    {
        yBallSpeed *= -1;
    }

    //TODO : IMPROVE HITBOXES
    //Different behaviors if the ball hits the side or the corner of a brick
    //Direction changes according to where the ball hits the player racket
    collisionManagement();
}

void collisionManagement()
{
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
            if (ballHitbox.intersects(bricks[i].getHitbox()))
            {
                bricks[i].brickGetsHit();
                if (bricks[i].getHealthPoints() == 0)
                {
                    bricks.erase(bricks.begin() + i);
                }
                yBallSpeed *= -1;
                hasCollided = true;
                collisionClock.restart();
            }
        }
    }

    if (collisionClock.getElapsedTime().asSeconds() > 0.2 && hasCollided)
    {
        hasCollided = false;
    }
}