#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Input
{
	struct KeyboardKey { bool left, right, start, escape, space; };
public:
	Input();
	void inputHandler(Event event, RenderWindow& window);
	KeyboardKey getKey() const;

private:
	KeyboardKey key;

};

#endif // !INPUT_H

