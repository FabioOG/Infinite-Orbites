#include "Carte.h"
#include <SFML/Graphics.hpp>


Carte::Carte(vector<Orbite> orbites)
{
    m_orbites=orbites;
}

Orbite* Carte::quelleOrbite(sf::Vector2f position)
{
    for (unsigned int i=0; i<m_orbites.size(); ++i)
    {
        if (m_orbites[i].estDedans(position)) return &m_orbites[i];
    }
    return NULL;
}

void Carte::redimensionner()
{
    for (unsigned int i=0; i<m_orbites.size(); ++i)
    {
        m_orbites[i].redimensionner();
    }
}

void Carte::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i=0; i<m_orbites.size(); ++i)
    {
        target.draw(m_orbites[i], states);
    }
}

