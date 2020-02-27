#include <cmath>
#include "operationsVecteurs.h"
#include <SFML/Graphics.hpp>

long double operator*(sf::Vector2f u, sf::Vector2f v) {
    return u.x*v.x + u.y*v.y;
}

sf::Vector2f operator*(long double a, sf::Vector2f u) {
    return sf::Vector2f(a*u.x,a*u.y);
}

sf::Vector2f operator*(sf::Vector2f u, long double a) {
    return sf::Vector2f(a*u.x,a*u.y);
}

float operator^(sf::Vector2f u, sf::Vector2f v) {
    return u.x*v.y-u.y*v.x;
}

sf::Vector2f rot(sf::Vector2f u){
    return sf::Vector2f(-u.y,u.x);
}

long double norme(sf::Vector2f u) {
    return sqrt(u*u);
}

sf::Vector2f normaliser(sf::Vector2f u) {
    return (1/norme(u))*u;
}

sf::Vector2f operator+(sf::Vector2f u, sf::Vector2f v) {
    return sf::Vector2f(u.x+v.x,u.y+v.y);
}

sf::Vector2f operator-(sf::Vector2f u) {
    return sf::Vector2f(-u.x,-u.y);
}
