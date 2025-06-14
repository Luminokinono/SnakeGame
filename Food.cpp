#include "Food.h"
#include "Snake.h"  // on inclut pour pouvoir utiliser Snake dans spawnFood
#include <SFML/Graphics.hpp>
#include <cstdlib>

Food::Food() : position(0, 0) {
    // Par d�faut position (0,0) - sera chang� par spawnFood
}

void Food::spawnFood(int gridWidth, int gridHeight, const Snake& snake) {
    while (true) {
        // choisi des coordonn�es al�atoires dans la grille
        int x = std::rand() % gridWidth;
        int y = std::rand() % gridHeight;
        sf::Vector2i newPos(x, y);
        // v�rifie que cette position n'est pas sur le serpent
        bool onSnake = false;
        if (snake.contains(x, y)) {
            onSnake = true;
        }
        if (!onSnake) {
            position = newPos;
            break;
        }
        // si la position �tait sur le serpent, on boucle pour tirer une nouvelle position al�atoire
    }
}

sf::Vector2i Food::getPosition() const {
    return position;
}

void Food::draw(sf::RenderWindow& window, int tileSize) const {
    sf::CircleShape circle;
    circle.setRadius(tileSize / 2.0f);
    circle.setFillColor(sf::Color::Red);
    // Le cercle par d�faut est centr� sur son point (0,0) en haut-gauche il faut ajuster la position 
    // pour centrer le cercle dans la case
    circle.setPosition(position.x * tileSize, position.y * tileSize);
    window.draw(circle);
}
