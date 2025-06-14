#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"
#include <cstdlib>
#include <ctime>
#include <sstream>

int main() {
    // Dimensions de la fenêtre et de la grille
    const int windowWidth = 800;
    const int windowHeight = 600;
    const int tileSize = 20;
    int gridWidth = windowWidth / tileSize;   // 40 cases
    int gridHeight = windowHeight / tileSize; // 30 cases

    // Création de la fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Snake SFML");
    window.setFramerateLimit(60); // Limite la boucle à 60 FPS 

    // Initialisation du générateur aléatoire
    std::srand(static_cast<unsigned>(time(nullptr)));

    // Création du serpent et de la nourriture
    Snake snake;
    Food food;
    // Position initiale du serpent 
    snake.initSnake(gridWidth / 2, gridHeight / 2);
    // Place une première nourriture aléatoirement
    food.spawnFood(gridWidth, gridHeight, snake);

    // Initialisation du texte de score
    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        // Gére l'erreur si le fichier de police n'est pas trouvé
    }
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(5, 5); // en haut à gauche
    scoreText.setString("Score : 0");

    int score = 0;
    bool gameOver = false;

    // Horloge pour gérer le timing du mouvement du serpent
    sf::Clock clock;
    float moveDelay = 0.1f;  // délai en secondes entre deux mouvements du serpent
    float timeSinceLastMove = 0.0f;

    // Boucle principale du jeu
    while (window.isOpen()) {
        // 1. Gestion des événements (clavier, fermeture de fenêtre)
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                // Gestion des touches fléchées pour changer la direction du serpent
                if (event.key.code == sf::Keyboard::Up)    snake.setDirection(Snake::UP);
                if (event.key.code == sf::Keyboard::Down)  snake.setDirection(Snake::DOWN);
                if (event.key.code == sf::Keyboard::Left)  snake.setDirection(Snake::LEFT);
                if (event.key.code == sf::Keyboard::Right) snake.setDirection(Snake::RIGHT);
            }
        }

        // 2. Mise à jour de l'état du jeu (déplacements, collisions) à intervalles réguliers
        float elapsed = clock.restart().asSeconds();
        timeSinceLastMove += elapsed;
        if (!gameOver && timeSinceLastMove >= moveDelay) {
            timeSinceLastMove = 0;

            // Déplacer le serpent d'un pas
            snake.move();

            // Vérifie si le serpent a mangé la nourriture
            if (snake.getHeadPosition() == food.getPosition()) {
                snake.grow();      // allonge le serpent
                score += 1;        // augmente le score
                scoreText.setString("Score : " + std::to_string(score));
                food.spawnFood(gridWidth, gridHeight, snake); // génére une nouvelle nourriture
            }

            // Vérifie les collisions 
            if (snake.isCollidingWithWall(gridWidth, gridHeight) || snake.isCollidingWithItself()) {
                gameOver = true;
                
            }
        }

        // 3. Affichage des éléments du jeu
        window.clear(); // effacer l'écran
        // Dessiner le serpent (chaque segment)
        snake.draw(window, tileSize);
        // Dessiner la nourriture
        food.draw(window, tileSize);
        // Dessiner le score
        window.draw(scoreText);
        window.display();
    }

    return 0;
}
