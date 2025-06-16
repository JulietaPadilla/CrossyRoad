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
    Nivel nivelActual;
    Sonido sonido;
    Ventana ventana;
    Puntaje puntaje;
    std::vector<Coleccionable> coleccionables; // Lista de coleccionables
    std::list<Obstaculo> obstaculos; // Lista de obstáculos
    bool juegoTerminado = false; // Indica si el juego ha terminado

public:
    JuegoCatCross() {}

    void InicializarColeccionables() {
        std::cout << "Debug: Inicializando coleccionables..." << std::endl;
        Coleccionable c1;
        if (!c1.CargarTextura("assets/images/Grass_02.png")) {
            std::cout << "Error: No se pudo cargar la textura del coleccionable 1." << std::endl;
        }
        c1.SetPosicion(100, 200);
        coleccionables.push_back(c1);

        Coleccionable c2;
        if (!c2.CargarTextura("assets/images/coleccionable2.png")) {
            std::cout << "Error: No se pudo cargar la textura del coleccionable 2." << std::endl;
        }
        c2.SetPosicion(300, 400);
        coleccionables.push_back(c2);
        std::cout << "Debug: Coleccionables inicializados correctamente." << std::endl;
    }

    void DibujarColeccionables(sf::RenderWindow& ventana) {
        for (auto& coleccionable : coleccionables) {
            coleccionable.Dibujar(ventana);
        }
    }

    void VerificarColisionesColeccionables() {
        std::cout << "Debug: Verificando colisiones con coleccionables..." << std::endl;
        sf::FloatRect jugadorBounds = personaje.GetSprite()->getGlobalBounds();
        for (auto& coleccionable : coleccionables) {
            if (!coleccionable.EsRecolectado() && coleccionable.GetSprite()->getGlobalBounds().intersects(jugadorBounds)) {
                std::cout << "Debug: Colisión detectada con un coleccionable." << std::endl;
                coleccionable.Recolectar();
                puntaje.Aumentar(10);
            }
        }
    }

    void VerificarColisionesObstaculos() {
        for (auto& obstaculo : obstaculos) {
            if (obstaculo.GetSprite()->getGlobalBounds().intersects(personaje.GetSprite()->getGlobalBounds())) {
                personaje.PerderVida();
                obstaculo.destruir();
                if (personaje.GetVidas() <= 0) {
                    juegoTerminado = true;
                }
            }
        }
    }

    void InicializarObstaculos() {
        Obstaculo o1;
        o1.CargarTextura("assets/images/obstaculo1.png");
        o1.SetPosicion(100, 500); // Adjusted position for visibility
        obstaculos.push_back(o1);

        Obstaculo o2;
        o2.CargarTextura("assets/images/obstaculo2.png");
        o2.SetPosicion(700, 300); // Adjusted position for visibility
        obstaculos.push_back(o2);
    }

    void DibujarObstaculos(sf::RenderWindow& ventana) {
        for (auto& obstaculo : obstaculos) {
            obstaculo.Dibujar(ventana);
        }
    }

    void ActualizarObstaculos() {
        for (auto& obstaculo : obstaculos) {
            obstaculo.Mover();
            if (obstaculo.GetSprite()->getGlobalBounds().intersects(personaje.GetSprite()->getGlobalBounds())) {
                std::cout << "Debug: Colisión detectada con un obstáculo." << std::endl;
                juegoTerminado = true; // Terminar el juego si hay colisión
            }
        }
    }

    void IniciarJuego() {
        std::cout << "Debug: Iniciando el juego..." << std::endl;
        InicializarColeccionables();
        InicializarObstaculos();

        while (ventana.EstaAbierta() && !juegoTerminado) {
            std::cout << "Debug: Ejecutando el bucle principal del juego..." << std::endl;
            ventana.ManejarEventos();
            VerificarColisionesColeccionables();
            VerificarColisionesObstaculos();
            ventana.Limpiar();

            std::vector<sf::Drawable*> elementos;
            for (auto& coleccionable : coleccionables) {
                elementos.push_back(coleccionable.GetSprite());
            }
            for (auto& obstaculo : obstaculos) {
                elementos.push_back(obstaculo.GetSprite());
            }
            elementos.push_back(personaje.GetSprite());

            ventana.MostrarElementos(elementos);
            sf::sleep(sf::seconds(1.f / 60.f));
        }

        if (juegoTerminado) {
            std::cout << "Debug: El juego ha terminado." << std::endl;
            MostrarPantallaFin();
        }
    }

    void MostrarPantallaInicio() {
        sf::RenderWindow ventana(sf::VideoMode(800, 600), "Cat Road");

        // Cargar la textura del fondo
        sf::Texture fondoTexture;
        if (!fondoTexture.loadFromFile("assets/images/fondo_inicio.png")) {
            throw std::runtime_error("No se pudo cargar la textura del fondo");
        }
        sf::Sprite fondoSprite(fondoTexture);

        // Cargar la fuente para el texto
        sf::Font fuente;
        if (!fuente.loadFromFile("assets/fonts/Platinum Sign.ttf")) {
            throw std::runtime_error("No se pudo cargar la fuente");
        }

        // Configurar el texto del título
        sf::Text titulo("CAT ROAD", fuente, 30);
        titulo.setFillColor(sf::Color::White);
        titulo.setPosition(250, 100);

        // Configurar las opciones del menú
        sf::Text opcionJugar("Presiona Enter para Jugar", fuente, 20);
        opcionJugar.setFillColor(sf::Color::White);
        opcionJugar.setPosition(200, 300);

        sf::Text opcionSalir("Presiona Esc para Salir", fuente, 20);
        opcionSalir.setFillColor(sf::Color::White);
        opcionSalir.setPosition(200, 400);

        bool iniciarJuego = false;

        while (ventana.isOpen()) {
            sf::Event evento;
            while (ventana.pollEvent(evento)) {
                if (evento.type == sf::Event::Closed) {
                    ventana.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    iniciarJuego = true;
                    ventana.close(); // Cerrar la pantalla de inicio y pasar al juego
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    ventana.close();
                    exit(0); // Salir del juego
                }
            }

            ventana.clear();
            ventana.draw(fondoSprite);
            ventana.draw(titulo);
            ventana.draw(opcionJugar);
            ventana.draw(opcionSalir);
            ventana.display();
        }

        if (iniciarJuego) {
            IniciarJuego();
        }
    }

    void MostrarPantallaFin() {
        sf::RenderWindow ventanaFin(sf::VideoMode(800, 600), "FIN DEL JUEGO");

        sf::Font fuente;
        if (!fuente.loadFromFile("assets/fonts/Platinum Sign.ttf")) {
            throw std::runtime_error("No se pudo cargar la fuente");
        }

        sf::Text textoFin("Juego Terminado", fuente, 50);
        textoFin.setFillColor(sf::Color::Red);
        textoFin.setPosition(200, 250);

        while (ventanaFin.isOpen()) {
            sf::Event evento;
            while (ventanaFin.pollEvent(evento)) {
                if (evento.type == sf::Event::Closed) {
                    ventanaFin.close();
                }
            }

            ventanaFin.clear();
            ventanaFin.draw(textoFin);
            ventanaFin.display();
        }
    }
};
