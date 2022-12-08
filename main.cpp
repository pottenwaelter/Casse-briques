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
            bricks[i + j * 6].getBrickPosition();
        }
    }

    //Placement du joueur
    player.setBrickPosition(WIN_WIDTH / 2, WIN_HEIGHT - 30);
    cout << getBrickSpacing() << endl;

    //Initialisation et placement de la balle
    ball.setFillColor(Color::Green);
    ball.setOutlineThickness(1);
    ball.setOutlineColor(Color::White);
    ball.setRadius(16.f);
    ball.setOrigin(16, 16);
    ball.setPosition(WIN_WIDTH / 2, WIN_HEIGHT / 2);

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

        window.clear();
        for (int i = 0; i < 24; i++)
        {
            window.draw(bricks[i]);
        }
        window.draw(player);
        window.draw(ball);
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
        }
    }

    if (player.getXPos() < WIN_WIDTH - playerWidth / 2)
    {
        if (input.getKey().right == true)
        {
            player.movePlayer("right");
        }
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