#ifndef TEXTES_H
#define TEXTES_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

//Prototypes de fonctions

class InGameText : public Drawable
{
public:
	InGameText();
	void setString(string str);
	void setPosition(float x, float y);
	void setCharSize(int size);
	void centerTextOrigin();
private:
	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		target.draw(m_text, states);
	}
	Font m_font;
	Text m_text;
	string m_str;
};

#endif //!TEXTES_H
