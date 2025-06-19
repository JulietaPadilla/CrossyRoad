#pragma once
#include <Gatito.h>
#include <Nivel.h>
#include <Sonido.h>
#include <Ventana.h>
#include <Puntaje.h>
#include <SFML/Graphics.hpp>
#include <Coleccionable.h>
#include <Obstaculo.h>
#include <vector>
#include <list>
#include <iostream> // Incluir iostream para mensajes de error

class JuegoCatCross {
private:
    Gatito personaje;
    Nivel nivel;
    int level = 1;
    float obstacleInterval = 0.35f;
    int lastPlayerRow;
    sf::Clock obstacleClock;
    Puntaje puntaje; // Puntaje del juego
public:
    void IniciarJuego() {
        const int WINDOW_WIDTH = 800;
        const int WINDOW_HEIGHT = 600;
        const int CELL_SIZE = 48;
        const int GRID_COLS = WINDOW_WIDTH / CELL_SIZE;
        const int GRID_ROWS = WINDOW_HEIGHT / CELL_SIZE;

        srand(static_cast<unsigned>(time(0)));
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Crossy Road");
        sf::Font font;
        if (!font.loadFromFile("assets/fonts/1up.ttf")) {
            std::cerr << "Error: No se pudo cargar la fuente." << std::endl;
            return;
        }
        sf::Text title("CROSSY ROAD", font, 50);
        sf::FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
        title.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100);
        sf::Text instructions("1.PRESIONA ENTER PARA COMENZAR\n2.ESC PARA SALIR", font, 30);
        sf::FloatRect instrBounds = instructions.getLocalBounds();
        instructions.setOrigin(instrBounds.width / 2, instrBounds.height / 2);
        instructions.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        while (window.isOpen()) {
            sf::Event event;
            bool startGame = false;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    startGame = true;
                    break;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                    return;
                }
            }
            if (startGame) break;
            window.clear();
            window.draw(title);
            window.draw(instructions);
            window.display();
        }
        
        // Pantalla de inicio SOLO debe llamarse desde main, no aquí
        // --- INICIO DEL JUEGO ---
        personaje.Reiniciar(GRID_COLS / 2, GRID_ROWS - 1);
        nivel = Nivel(GRID_COLS, GRID_ROWS);
        // Dificultad baja al iniciar
        nivel.GenerarObstaculosAvanzado(1);
        lastPlayerRow = personaje.GetGridY();
        puntaje.Reiniciar(); // Reinicia el puntaje al iniciar el juego
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                personaje.MoverArriba();
                // Esperar hasta que se suelte la tecla para evitar múltiples movimientos
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {}
                sf::sleep(sf::milliseconds(40));
                puntaje.Aumentar(1); // Suma puntaje al avanzar
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {}
                sf::sleep(sf::milliseconds(40));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                personaje.MoverIzquierda();
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {}
                sf::sleep(sf::milliseconds(40));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                personaje.MoverDerecha(GRID_COLS - 1);
                while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {}
                sf::sleep(sf::milliseconds(40));
            }
            if (personaje.GetGridY() < lastPlayerRow) {
                level++;
                // Aumenta dificultad SOLO al avanzar de nivel
                obstacleInterval = std::max(0.06f, obstacleInterval - 0.015f);
                lastPlayerRow = personaje.GetGridY();
                if (personaje.GetGridY() == 0) {
                    personaje.Reiniciar(GRID_COLS / 2, GRID_ROWS - 1);
                    nivel = Nivel(GRID_COLS, GRID_ROWS);
                    nivel.GenerarObstaculosAvanzado(level); // dificultad ajustada por nivel solo al avanzar
                    lastPlayerRow = personaje.GetGridY();
                }
            }
            nivel.ActualizarObstaculosAvanzado();
            bool collisionDetected = false;
            for (auto& obstaculo : nivel.GetObstaculos()) {
                if (personaje.GetGridX() == obstaculo.GetGridX() && personaje.GetGridY() == obstaculo.GetGridY()) {
                    collisionDetected = true;
                    break;
                }
            }
            if (collisionDetected) {
                std::cout << "Game Over!" << std::endl;
                break;
            }
            personaje.ActualizarAnimacion();
            window.clear();
            window.draw(personaje.GetSprite());
            // Dibuja solo los obstáculos activos y siempre como sprite
            for (auto& obstaculo : nivel.GetObstaculos()) {
                if (obstaculo.EstaActivo()) {
                    window.draw(obstaculo.GetSprite());
                }
            }
            puntaje.Dibujar(window);
            window.display();
        }
        std::cout << "Debug: Juego terminado." << std::endl;
    }

    void MostrarPantallaInicio() {
        const int WINDOW_WIDTH = 800;
        const int WINDOW_HEIGHT = 600;
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Crossy Road - Inicio");
        sf::Font font;
        if (!font.loadFromFile("assets/fonts/1up.ttf")) {
            std::cerr << "Error: No se pudo cargar la fuente." << std::endl;
            return;
        }
        sf::Text title("CROSSY ROAD", font, 50);
        sf::FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
        title.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100);
        sf::Text instructions("Presiona Enter para comenzar", font, 30);
        sf::FloatRect instrBounds = instructions.getLocalBounds();
        instructions.setOrigin(instrBounds.width / 2, instrBounds.height / 2);
        instructions.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

        while (window.isOpen()) {
            sf::Event event;
            bool startGame = false;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    startGame = true;
                    break;
                }
                
            }
            if (startGame) break;
            window.clear();
            window.draw(title);
            window.draw(instructions);
            window.display();
        }
    }

};
