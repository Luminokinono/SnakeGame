#include <SFML/Graphics.hpp>
// Snake.cpp
#include "Snake.h"

Snake::Snake() : dir(RIGHT), pendingDir(RIGHT) {
    // le serpent va vers la droite
}

void Snake::initSnake(int startX, int startY) {
    segments.clear();
    // On crée un serpent initial de longueur 3 par exemple, horizontal
    segments.push_back({ startX, startY });       // tête
    segments.push_back({ startX - 1, startY });   // corps
    segments.push_back({ startX - 2, startY });   // queue
    dir = RIGHT;
    pendingDir = RIGHT;
}

void Snake::setDirection(Direction newDir) {
    if ((dir == UP && newDir == DOWN) || (dir == DOWN && newDir == UP) ||
        (dir == LEFT && newDir == RIGHT) || (dir == RIGHT && newDir == LEFT)) {
        return;
    }
    // On enregistre la nouvelle direction demandée
    pendingDir = newDir;
}

void Snake::move() {
    // Appliquer la direction demandée par le joueur 
    // comme nouvelle direction actuelle avant de bouger
    dir = pendingDir;

    // Calculer la nouvelle position de tête en fonction de la direction
    sf::Vector2i head = segments.front();
    switch (dir) {
    case UP:    head.y -= 1; break;
    case DOWN:  head.y += 1; break;
    case LEFT:  head.x -= 1; break;
    case RIGHT: head.x += 1; break;
    }
    // Insére la nouvelle tête au début de la deque
    segments.push_front(head);
    // Supprime le dernier segment (queue) pour avancer 
    segments.pop_back();
}

void Snake::grow() {
    // Pour faire grandir le serpent on ajoute un segment supplémentaire.
    sf::Vector2i tail = segments.back();
    segments.push_back(tail);
    // lors du prochain move(), on ajoutera une tête et 
    // en retirant un segment de queue, on retirera ce qu'on vient d'ajouter 
    // au lieu de la queue originale ce qui maintient la longueur +1
}

sf::Vector2i Snake::getHeadPosition() const {
    return segments.front();
}

bool Snake::isCollidingWithItself() const {
    if (segments.size() < 2) return false;
    sf::Vector2i head = segments.front();
    // Commencer à parcourir à partir du segment suivant la tête (i=1)
    for (size_t i = 1; i < segments.size(); ++i) {
        if (segments[i] == head) {
            return true;
        }
    }
    return false;
}

bool Snake::isCollidingWithWall(int gridWidth, int gridHeight) const {
    sf::Vector2i head = segments.front();
    if (head.x < 0 || head.x >= gridWidth || head.y < 0 || head.y >= gridHeight) {
        return true;
    }
    return false;
}

void Snake::draw(sf::RenderWindow& window, int tileSize) const {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(tileSize - 1, tileSize - 1));
    for (size_t i = 0; i < segments.size(); ++i) {
        rect.setPosition(segments[i].x * tileSize, segments[i].y * tileSize);
        if (i == 0) {
            rect.setFillColor(sf::Color::Yellow); // tête en jaune pour la distinguer du corps
        }
        else {
            rect.setFillColor(sf::Color::Green);  // corps en vert
        }
        window.draw(rect);
    }
}

bool Snake::contains(int x, int y) const {
    for (const auto& segment : segments) {
        if (segment.x == x && segment.y == y) {
            return true;
        }
    }
    return false;
}
