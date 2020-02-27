#include "../include/CanevasJeu.h"

using namespace std;

CanevasJeu::CanevasJeu(float largeur,float hauteur)
{
    redimensionner(largeur,hauteur);
}

void CanevasJeu::redimensionner(float largeur,float hauteur)
{
    float resolution=min(hauteur,largeur*9/16);
    if (hauteur==resolution) offset=sf::Vector2f(((float)largeur-16.0*(float)resolution/9.0)/2.0,0);
    else offset=sf::Vector2f(0,(float)(hauteur-resolution)/2.0);

    echelle=(double)resolution/1080.0;

    bords = sf::Vector2f(1920*echelle,1080*echelle);
}
