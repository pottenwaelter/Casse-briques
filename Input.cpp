#include "Input.h"

Input::Input()
{
	key.left = key.right = key.start = key.escape = key.backspace = key.space = false;
}

Input::KeyboardKey Input::getKey() const
{
	return key;
}

void Input::inputHandler(Event event, RenderWindow& window)
{
	if (event.type == Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case Keyboard::Escape:
			key.escape = true;
			break;
		case Keyboard::Q:
			key.left = true;
			break;
		case Keyboard::D:
			key.right = true;
			break;
		case Keyboard::Enter:
			key.start = true;
			break;
		case Keyboard::Space:
			key.space = true;
			break;
		case Keyboard::Backspace:
			key.backspace = true;
			break;
		default:
			break;
		}
	}

	if (event.type == Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case Keyboard::Escape:
			key.escape = false;
			break;
		case Keyboard::Q:
			key.left = false;
			break;
		case Keyboard::D:
			key.right = false;
			break;
		case Keyboard::Enter:
			key.start = false;
			break;
		case Keyboard::Space:
			key.space = false;
			break;
		case Keyboard::Backspace:
			key.backspace = false;
			break;
		default:
			break;
		}
	}

}
