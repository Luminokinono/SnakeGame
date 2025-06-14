#include <SFML/Graphics.hpp>
// Snake.h
#pragma once
#include <SFML/System/Vector2.hpp>
#include <deque>

class Snake {
public:
    // Directions possibles pour le serpent
    enum Direction { UP, DOWN, LEFT, RIGHT };

    Snake();
    void initSnake(int startX, int startY);
    void setDirection(Direction newDir);
    void move();
    void grow();
    sf::Vector2i getHeadPosition() const;
    bool isCollidingWithItself() const;
    bool isCollidingWithWall(int gridWidth, int gridHeight) const;
    void draw(sf::RenderWindow& window, int tileSize) const;
    bool contains(int x, int y) const;


private:
    std::deque<sf::Vector2i> segments; // deque de positions des segments (de la tête à la queue)
    Direction dir;                     // direction actuelle du serpent
    Direction pendingDir;              // direction en attente (pour éviter les demi-tours instantanés)
};
#pragma once
