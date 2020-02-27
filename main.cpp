#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "include/Joueur.h"
#include "include/Carte.h"
#include "include/CanevasJeu.h"

using namespace std;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // On crée une fenêtre de jeu de la taille de l'écran appelée "Infinite Orbits"
    sf::RenderWindow fenetreJeu(sf::VideoMode::getDesktopMode(), "Infinite Orbits", sf::Style::Default);
    int largeur=fenetreJeu.getSize().x;
    int hauteur=fenetreJeu.getSize().y;
    fenetreJeu.setKeyRepeatEnabled(false); // pas de répétition d'appui sur la touche

    // Calcul de la fenêtre de jeu en 16/9 et création du canevas
    CanevasJeu canevas(largeur,hauteur);

    // création de la carte
    vector<Orbite> orbites;
    orbites.push_back(Orbite(&canevas, sf::Vector2f(1000,500), 500));
    Carte carte(orbites);

    // Remplissage en blanc de la fenêtre de jeu
    sf::RectangleShape fond(sf::Vector2f(1920*canevas.getEchelle(),1080*canevas.getEchelle()));
    fond.setPosition(canevas.getOffset());
    fond.setFillColor(sf::Color::White);

    // Création du joueur
    Joueur joueur1(&canevas,&carte);
    sf::Clock temps;

	// Boucle du jeu
    while (fenetreJeu.isOpen())
    {

        // Gestion des évènements
        sf::Event event;
        while (fenetreJeu.pollEvent(event))
        {
            // Fermer la fenêtre
            if (event.type == sf::Event::Closed)
                fenetreJeu.close();

            // Gestion du changement de taille de fenêtre
            if (event.type == sf::Event::Resized) {
                largeur=event.size.width;
                hauteur=event.size.height;

                // On crée une fenêtre 16/9 la plus grande possible à l'intérieur de la fenêtre
                canevas.redimensionner(largeur,hauteur);

                // Redimensionement du jeu
                fond.setSize(sf::Vector2f(1920*canevas.getEchelle(),1080*canevas.getEchelle()));
                fond.setPosition(canevas.getOffset());
                carte.redimensionner();

                fenetreJeu.setView(sf::View(sf::FloatRect(0,0,largeur,hauteur)));
            }

            joueur1.evenements(event); // Gestion des évenements du joueur
        }

        // Effacer l'écran pour afficher l'image suivante
        fenetreJeu.clear();

        // Tick
        sf::Time delta = temps.restart();
        joueur1.deplacement(delta);

        // Dessin de l'image
        fenetreJeu.draw(fond);
        fenetreJeu.draw(carte);
        fenetreJeu.draw(joueur1);

        fenetreJeu.display();
    }

    return EXIT_SUCCESS;
}
