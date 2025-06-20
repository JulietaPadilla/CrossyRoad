#pragma once
#include <Gatito.h>
#include <Nivel.h>
#include <Sonido.h>
#include <Puntaje.h>
#include <SFML/Graphics.hpp>
#include <Coleccionable.h>
#include <Obstaculo.h>
#include <vector>
#include <list>
#include <iostream> // Incluir iostream para mensajes de error
#include <Usuario.h>

class JuegoCatCross {
private:
    Gatito personaje;
    Nivel nivel;
    int nivelActual = 1;
    float intervaloObstaculo = 0.35f;
    int ultimaFilaJugador;
    sf::Clock relojObstaculo;
    Puntaje puntaje; // Puntaje del juego
    Usuario usuario; // Usuario actual
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
        if (!font.loadFromFile("assets/fonts/Pirata.ttf")) {
            std::cerr << "Error: No se pudo cargar la fuente." << std::endl;
            return;
        }
        sf::Text title("CROSSY ROAD", font, 100);
        sf::FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
        title.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 200);
        title.setFillColor(sf::Color::Black);
        sf::Text instructions("- PRESIONA ENTER PARA COMENZAR\n - ESC PARA SALIR", font, 40);
        sf::FloatRect instrBounds = instructions.getLocalBounds();
        instructions.setOrigin(instrBounds.width / 2, instrBounds.height / 2);
        instructions.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 80);
        instructions.setFillColor(sf::Color::Black);
        // Cargar fondo para el menú y pantallas previas
        sf::Texture fondoMenuTexture;
        if (!fondoMenuTexture.loadFromFile("assets/images/fondo_juego2.jpeg")) {
            std::cerr << "Error: No se pudo cargar la imagen de fondo del menú." << std::endl;
        }
        sf::Sprite fondoMenuSprite;
        fondoMenuSprite.setTexture(fondoMenuTexture);
        fondoMenuSprite.setScale(
            float(WINDOW_WIDTH) / fondoMenuTexture.getSize().x,
            float(WINDOW_HEIGHT) / fondoMenuTexture.getSize().y
        );
        // --- PRIMERA PANTALLA: Espera Enter para ingresar nombre ---
        while (window.isOpen()) {
            sf::Event event;
            bool startInput = false;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    startInput = true;
                    break;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                    return;
                }
            }
            if (startInput) break;
            window.clear();
            window.draw(fondoMenuSprite);
            window.draw(title);
            window.draw(instructions);
            window.display();
        }
        // --- SEGUNDA PANTALLA: Ingreso de nombre de usuario ---
        std::string nombreUsuario = "";
        bool nombreIngresado = false;
        sf::Text inputText("", font, 40);
        inputText.setFillColor(sf::Color::Black);
        sf::Text prompt(">> Ingresa tu nombre y presiona Enter:", font, 50);
        prompt.setFillColor(sf::Color::Black);
        sf::FloatRect promptBounds = prompt.getLocalBounds();
        prompt.setOrigin(promptBounds.width / 2, promptBounds.height / 2);
        prompt.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100);
        inputText.setOrigin(0, 0);
        while (window.isOpen() && !nombreIngresado) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') { // Backspace
                        if (!nombreUsuario.empty()) nombreUsuario.pop_back();
                    } else if (event.text.unicode == '\r' || event.text.unicode == '\n') { // Enter
                        if (!nombreUsuario.empty()) nombreIngresado = true;
                    } else if (event.text.unicode < 128 && nombreUsuario.size() < 16 && event.text.unicode != 27) {
                        nombreUsuario += static_cast<char>(event.text.unicode);
                    }
                }
            }
            inputText.setString(nombreUsuario);
            sf::FloatRect inputBounds = inputText.getLocalBounds();
            inputText.setOrigin(inputBounds.width / 2, 0);
            inputText.setPosition(WINDOW_WIDTH / 2 + 200, WINDOW_HEIGHT / 2 - 50);
            window.clear();
            window.draw(fondoMenuSprite);
            window.draw(title);
            window.draw(prompt);
            window.draw(inputText);
            window.display();
        }
        usuario.SetNombre(nombreUsuario);
        // Cargar puntaje máximo del usuario
        std::string archivoPuntaje = "puntaje_" + nombreUsuario + ".dat";
        usuario.CargarPuntuacionMaxima(archivoPuntaje);
        // Mostrar puntaje máximo antes de iniciar el juego
        sf::Text maxScoreText("Puntaje maximo: " + std::to_string(usuario.ObtenerPuntuacionMaxima()), font, 40);
        maxScoreText.setFillColor(sf::Color::Black);
        maxScoreText.setPosition(WINDOW_WIDTH / 2 + 80, WINDOW_HEIGHT / 2 + 30);
        bool mostrarMax = true;
        while (window.isOpen() && mostrarMax) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    mostrarMax = false;
                    break;
                }
            }
            window.clear();
            window.draw(fondoMenuSprite);
            window.draw(title);
            window.draw(prompt);
            window.draw(inputText);
            window.draw(maxScoreText);
            window.display();
        }
        // --- INICIO DEL JUEGO ---
        personaje.Reiniciar(GRID_COLS / 2, GRID_ROWS - 1);
        nivel = Nivel(GRID_COLS, GRID_ROWS);
        nivel.GenerarObstaculosAvanzado(1);
        ultimaFilaJugador = personaje.GetGridY();
        puntaje.Reiniciar();
        // Cargar fondo para el juego principal
        sf::Texture juegoFondoTexture;
        if (!juegoFondoTexture.loadFromFile("assets/images/fondo_juego.jpeg")) {
            std::cerr << "Error: No se pudo cargar la imagen de fondo para el juego." << std::endl;
        }
        sf::Sprite juegoFondoSprite;
        juegoFondoSprite.setTexture(juegoFondoTexture);
        juegoFondoSprite.setScale(
            float(WINDOW_WIDTH) / juegoFondoTexture.getSize().x,
            float(WINDOW_HEIGHT) / juegoFondoTexture.getSize().y
        );
        sf::Clock inputClock; // Reloj para controlar el cooldown de movimiento
        // Estados previos de las teclas
        bool prevUp = false, prevDown = false, prevLeft = false, prevRight = false;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            // Detectar flanco de bajada para cada tecla
            bool currUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
            bool currDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
            bool currLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
            bool currRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
            bool moved = false;
            if (currUp && !prevUp) {
                personaje.MoverArriba();
                puntaje.Aumentar(1);
                moved = true;
            }
            if (currDown && !prevDown) {
                personaje.MoverAbajo(GRID_ROWS - 1);
                moved = true;
            }
            if (currLeft && !prevLeft) {
                personaje.MoverIzquierda();
                moved = true;
            }
            if (currRight && !prevRight) {
                personaje.MoverDerecha(GRID_COLS - 1);
                moved = true;
            }
            prevUp = currUp;
            prevDown = currDown;
            prevLeft = currLeft;
            prevRight = currRight;
            if (moved) {
                inputClock.restart();
            }
            if (personaje.GetGridY() < ultimaFilaJugador) {
                nivelActual++;
                intervaloObstaculo = std::max(0.06f, intervaloObstaculo - 0.015f);
                ultimaFilaJugador = personaje.GetGridY();
                if (personaje.GetGridY() == 0) {
                    personaje.Reiniciar(GRID_COLS / 2, GRID_ROWS - 1);
                    nivel = Nivel(GRID_COLS, GRID_ROWS);
                    nivel.GenerarObstaculosAvanzado(nivelActual);
                    ultimaFilaJugador = personaje.GetGridY();
                }
            }
            nivel.ActualizarObstaculosAvanzado();
            bool collisionDetected = false;
            for (auto& obstaculo : nivel.GetObstaculos()) {
                int obsX = obstaculo.GetGridX();
                int obsY = obstaculo.GetGridY();
                int obsLargo = obstaculo.GetLargo();
                if (personaje.GetGridY() == obsY &&
                    personaje.GetGridX() >= obsX &&
                    personaje.GetGridX() < obsX + obsLargo) {
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
            window.draw(juegoFondoSprite);
            window.draw(personaje.GetSprite());
            for (auto& obstaculo : nivel.GetObstaculos()) {
                if (obstaculo.EstaActivo()) {
                    window.draw(obstaculo.GetSprite());
                }
            }
            puntaje.Dibujar(window);
            window.display();
        }
        // Al final del juego, guardar puntaje máximo
        usuario.SetPuntuacionMaxima(puntaje.ObtenerMaximo());
        usuario.GuardarPuntuacionMaxima(archivoPuntaje);
        std::cout << "Debug: Juego terminado." << std::endl;
    }

    void MostrarPantallaInicio() {
        const int WINDOW_WIDTH = 800;
        const int WINDOW_HEIGHT = 600;
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Crossy Road - Inicio");
        sf::Font font;
        if (!font.loadFromFile("assets/fonts/Pirata.ttf")) {
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
        // Cargar fondo para el menú
        sf::Texture fondoTexture;
        if (!fondoTexture.loadFromFile("assets/images/fondo_juego2.jpeg")) {
            std::cerr << "Error: No se pudo cargar la imagen de fondo." << std::endl;
        }
        sf::Sprite fondoSprite;
        fondoSprite.setTexture(fondoTexture);
        fondoSprite.setScale(
            float(WINDOW_WIDTH) / fondoTexture.getSize().x,
            float(WINDOW_HEIGHT) / fondoTexture.getSize().y
        );
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
            window.draw(fondoSprite);
            window.draw(title);
            window.draw(instructions);
            window.display();
        }
    }

};
