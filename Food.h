#include <SFML/Graphics.hpp>
// Food.h
#pragma once
#include <SFML/System/Vector2.hpp>

class Food {
public:
    Food();
    void spawnFood(int gridWidth, int gridHeight, const class Snake& snake);
    sf::Vector2i getPosition() const;
    void draw(sf::RenderWindow& window, int tileSize) const;
private:
    sf::Vector2i position;
};
#pragma once
