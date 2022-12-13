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
    player.setBrickPosition(WIN_WIDTH / 2, WIN_HEIGHT - 30);

    //Initialisation et placement de la balle
    ball.setFillColor(Color::Green);
    ball.setOutlineThickness(1);
    ball.setOutlineColor(Color::White);
    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius, ballRadius);
    ball.setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);

    //Définition des 3 différentes hitboxes du joueur
    playerRects[0].setSize(Vector2f(65, 20));
    playerRects[0].setPosition(player.getXPos() - playerWidth / 2, player.getYPos() - playerHeight / 2);
    playerRects[0].setFillColor(Color::White);

    playerRects[1].setSize(Vector2f(20, 20));
    playerRects[1].setPosition(playerRects[0].getPosition().x + 65, playerRects[0].getPosition().y);
    playerRects[1].setFillColor(Color::White);

    playerRects[2].setSize(Vector2f(65, 20));
    playerRects[2].setPosition(playerRects[1].getPosition().x + 20, playerRects[1].getPosition().y);
    playerRects[2].setFillColor(Color::White);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            input.inputHandler(event, window);
        }

        for (int i = 0; i < 3; i++)
        {
            playerHitboxes[i] = playerRects[i].getGlobalBounds();
        }
        checkInput();
        if (hasGameStarted)
        {
            ballMovement();
        }

        window.clear();
        for (int i = 0; i < 24; i++)
        {
            window.draw(bricks[i]);
        }
        window.draw(player);
        window.draw(ball);
        if (checkPlayerHitbox)
        {
            for (int i = 0; i < 3; i++)
            {
                window.draw(playerRects[i]);
            }
        }
        //cout << playerHitboxes[0].left << endl;
        //cout << ballHitbox.left << endl;
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
            for (int i = 0; i < 3; i++)
            {
                playerRects[i].move(-4, 0);
            }
        }
    }

    if (player.getXPos() < WIN_WIDTH - playerWidth / 2)
    {
        if (input.getKey().right == true)
        {
            player.movePlayer("right");
            for (int i = 0; i < 3; i++)
            {
                playerRects[i].move(4, 0);
            }
        }
    }

    if (input.getKey().space == true)
    {
        hasGameStarted = true;
    }

    if (input.getKey().backspace == true)
    {
        checkPlayerHitbox = true;
    }
    else
    {
        checkPlayerHitbox = false;
    }

    if (input.getKey().escape == true)
    {
        window.close();
    }
}

float getBrickSpacing()
{
    float totalWidth = 150 * 6; // largeur totale du rectangle de l'ensemble des briques
    float spacing = (WIN_WIDTH - totalWidth) / 2;

    return spacing;
}

void ballMovement()
{
    ballHitbox = ball.getGlobalBounds();
    ball.move(xBallSpeed, -yBallSpeed);
    if (ball.getPosition().x < 1 + ballRadius || ball.getPosition().x >= WIN_WIDTH - ballRadius)
    {
        xBallSpeed *= -1;
    }

    if (ball.getPosition().y < 1 + ballRadius || ball.getPosition().y >= WIN_HEIGHT - ballRadius)
    {
        yBallSpeed *= -1;
    }

    //TODO : FIX THE WHOLE THING :-]

    if (!hasCollided)
    {
        if (ballHitbox.intersects(playerHitboxes[0]))
        {
            cout << "Collision gauche" << endl;
            yBallSpeed *= -1;
            hasCollided = true;
            collisionClock.restart();
        }

        if (ballHitbox.intersects(playerHitboxes[1]))
        {
            cout << "Collision milieu" << endl;
            yBallSpeed *= -1;
            xBallSpeed /= 4;
            hasCollided = true;
            collisionClock.restart();
        }

        if (ballHitbox.intersects(playerHitboxes[2]))
        {
            cout << "Collision droite" << endl;
            yBallSpeed *= -1;
            hasCollided = true;
            collisionClock.restart();
        }
    }

    if (collisionClock.getElapsedTime().asSeconds() > 0.5 && hasCollided)
    {
        hasCollided = false;
    }
}