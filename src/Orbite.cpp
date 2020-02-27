#include "Orbite.h"


Orbite::Orbite(CanevasJeu* canevas, sf::Vector2f position, float rayon, sf::Color couleur)
{
   m_canevas=canevas;

   m_position=position;
   m_rayon=rayon;
   m_forme=sf::CircleShape(m_rayon*m_canevas->getEchelle(),m_rayon*2);
   m_couleur=couleur;

   m_forme.setFillColor(couleur);
   m_forme.setPosition(m_position*m_canevas->getEchelle()+m_canevas->getOffset()-sf::Vector2f(m_rayon,m_rayon));
}

float Orbite::distance(sf::Vector2f position)
{
    return norme(position-m_position);
}

bool Orbite::estDedans(sf::Vector2f position)
{
    return (distance(position)<=m_rayon);
}

void Orbite::redimensionner()
{
    m_forme.setPosition((m_position-sf::Vector2f(m_rayon,m_rayon))*m_canevas->getEchelle()+m_canevas->getOffset());
    m_forme.setRadius(m_rayon*m_canevas->getEchelle());
}

void Orbite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_forme,states);
}

