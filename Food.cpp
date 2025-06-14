#include "Food.h"
#include "Snake.h"  // on inclut pour pouvoir utiliser Snake dans spawnFood
#include <SFML/Graphics.hpp>
#include <cstdlib>

Food::Food() : position(0, 0) {
    // Par défaut position (0,0) - sera changé par spawnFood
}

void Food::spawnFood(int gridWidth, int gridHeight, const Snake& snake) {
    while (true) {
        // choisi des coordonnées aléatoires dans la grille
        int x = std::rand() % gridWidth;
        int y = std::rand() % gridHeight;
        sf::Vector2i newPos(x, y);
        // vérifie que cette position n'est pas sur le serpent
        bool onSnake = false;
        if (snake.contains(x, y)) {
            onSnake = true;
        }
        if (!onSnake) {
            position = newPos;
            break;
        }
        // si la position était sur le serpent, on boucle pour tirer une nouvelle position aléatoire
    }
}

sf::Vector2i Food::getPosition() const {
    return position;
}

void Food::draw(sf::RenderWindow& window, int tileSize) const {
    sf::CircleShape circle;
    circle.setRadius(tileSize / 2.0f);
    circle.setFillColor(sf::Color::Red);
    // Le cercle par défaut est centré sur son point (0,0) en haut-gauche il faut ajuster la position 
    // pour centrer le cercle dans la case
    circle.setPosition(position.x * tileSize, position.y * tileSize);
    window.draw(circle);
}
