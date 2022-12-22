#include "Textes.h"

InGameText::InGameText()
{
    if (!m_font.loadFromFile("ressources/font/verdana.ttf"))
    {
        cerr << "Erreur chargement police d'ecriture" << endl;
    }
    m_text.setFont(m_font);
    m_str = "";
    m_text.setString(m_str);
    m_text.setFillColor(Color(255, 255, 255, 200));
}

void InGameText::setString(string str)
{
    m_text.setString(str);
}

void InGameText::setPosition(float x, float y)
{
    m_text.setPosition(x, y);
}

void InGameText::setCharSize(int size)
{
    m_text.setCharacterSize(size);
}

void InGameText::centerTextOrigin()
{
    m_text.setOrigin(round(m_text.getLocalBounds().left + m_text.getLocalBounds().width / 2),
                    round(m_text.getLocalBounds().top + m_text.getLocalBounds().height / 2));
}


