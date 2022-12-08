#include "main.h"

int main()
{
    window.setFramerateLimit(60);
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
            bricks[i + j * 6].setBrickPosition((20 + i * bricks[i].getBrickWidth()), (20 + j * bricks[i].getBrickHeight()));
            bricks[i + j * 6].getBrickPosition();
        }
    }
    //Placement du joueur
    player.setBrickPosition(1200 / 2, 720-30);

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
        window.display();
    }

    return 0;
}

void checkInput()
{
    if (player.getXPos() > 75)
    {
        if (input.getKey().left == true)
        {
            player.movePlayer("left");
        }
    }

    if (player.getXPos() < 1200 - 75)
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