#include "Joueur.h"
#include <cmath>
#include <iostream>

using namespace std;

#include "operationsVecteurs.h"
#include "../include/Orbite.h"

Joueur::Joueur(CanevasJeu *_canevas, Carte *_carte)
{
    canevas = _canevas;

    taille=30;
    forme = sf::CircleShape(taille * canevas->getEchelle(),taille);
    forme.setFillColor(sf::Color::Green);

    position = sf::Vector2f(1000,500);
    vitesse = sf::Vector2f(200,100); // en px/s pour du 1080p
    orbite = NULL;
    carte=_carte;
    omega=0;
    theta=0;
    rayon=0;

    touche = sf::Keyboard::Space;
    tempsAccRestant = sf::Time::Zero;
}

void Joueur::choc(sf::Vector2f direction) {
    direction = normaliser(direction);
    vitesse = abs(vitesse*direction)*direction + (vitesse*rot(direction))*rot(direction);
}

sf::Keyboard::Key Joueur::getTouche() const {
    return touche;
}

void Joueur::deplacement(sf::Time delta) {

    if      (position.x /* * resolution/1080 */<= forme.getRadius()) choc(sf::Vector2f(1,0));
    else if (position.x * canevas->getEchelle() >= canevas->getBords().x-forme.getRadius()) choc(sf::Vector2f(-1,0));
    else if (position.y /* * resolution/1080 */<= forme.getRadius()) choc(sf::Vector2f(0,1));
    else if (position.y * canevas->getEchelle() >= canevas->getBords().y-forme.getRadius()) choc(sf::Vector2f(0,-1));

    if (orbite==NULL) {
        position+=delta.asSeconds()*vitesse*(1+BONUS*(tempsAccRestant!=sf::Time::Zero)); // on avance selon la vitesse + bonus si accélération

        tempsAccRestant-=delta;
        if (tempsAccRestant<sf::Time::Zero) tempsAccRestant=sf::Time::Zero;
    }
    else
    {
        theta+=(omega)*delta.asSeconds();
        position=sf::Vector2f(cos(theta)*rayon,sin(theta)*rayon)+orbite->getPosition();
    }

    forme.setRadius(canevas->getEchelle() * taille);
    forme.setPosition((position-sf::Vector2f(taille,taille))*canevas->getEchelle()+canevas->getOffset());
}

void Joueur::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(forme,states);
}

void Joueur::evenements(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == touche) {

            if (orbite)
            {
                vitesse=omega*rayon*sf::Vector2f(-sin(theta),cos(theta));
                orbite=NULL;
                return;
            }

            orbite=carte->quelleOrbite(position);
            if (!orbite) {tempsAccRestant=sf::seconds(TEMPSACC);} // Si orbite pas d'acc
            else
            {
                sf::Vector2f posRelative=position-orbite->getPosition();
                rayon=norme(posRelative);
                bool omegaPos = ((posRelative^vitesse)>0);
                if (omegaPos) omega=norme(vitesse)/rayon;
                else omega=-norme(vitesse)/rayon;

                theta = acos(posRelative.x/rayon);
                if (posRelative.y<0) theta *= -1;

                tempsAccRestant=sf::Time::Zero;

            }
        }
    }
}

