#include "main.h"

int main()
{
    RenderWindow window(VideoMode(1200, 720), "Casse-briques");
    window.setFramerateLimit(60);
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

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        for (int i = 0; i < 24; i++)
        {
            window.draw(bricks[i]);
        }
        window.display();
    }

    return 0;
}