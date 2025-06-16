#pragma once
#include <Gatito.h>
#include <Nivel.h>
#include <Sonido.h>
#include <Ventana.h>
#include <Puntaje.h>
#include <SFML/Graphics.hpp>
#include <Coleccionable.h>
#include <vector>

class JuegoCatCross {
private:
    Gatito personaje;
    Nivel nivelActual;
    Sonido sonido;
    Ventana ventana;
    Puntaje puntaje;
    std::vector<Coleccionable> coleccionables; // Lista de coleccionables

public:
    JuegoCatCross() {}

    void InicializarColeccionables() {
        Coleccionable c1;
        c1.CargarTextura("assets/coleccionable1.png");
        c1.SetPosicion(100, 200);
        coleccionables.push_back(c1);

        Coleccionable c2;
        c2.CargarTextura("assets/coleccionable2.png");
        c2.SetPosicion(300, 400);
        coleccionables.push_back(c2);
    }

    void DibujarColeccionables(sf::RenderWindow& ventana) {
        for (auto& coleccionable : coleccionables) {
            coleccionable.Dibujar(ventana);
        }
    }

    void VerificarColisionesColeccionables() {
        sf::FloatRect jugadorBounds = personaje.getSprite(); // Obtener los límites del sprite del personaje
        for (auto& coleccionable : coleccionables) {
            if (!coleccionable.EsRecolectado() && coleccionable.GetSprite().getGlobalBounds().intersects(jugadorBounds)) {
                coleccionable.Recolectar();
                puntaje.Aumentar(10); // Incrementar puntaje al recolectar
            }
        }
    }

    void IniciarJuego() {

        const int anchoVentana = 800;
        const int altoVentana = 600;
        
        //creacion del objeto y carga de la fuente
        sf::Font font;
        if (!font.loadFromFile("assets/fonts/Platinum Sign.ttf")) {
            // Manejo de error: fuente no encontrada
        }
        InicializarColeccionables();
        while (ventana.EstaAbierta()) {
            ventana.ManejarEventos();


            // Manejo de teclado para mover al gatito con límites de ventana
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                personaje.MoverArriba(0); // Límite superior
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                personaje.MoverAbajo(altoVentana);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                personaje.MoverIzquierda(0); // Límite izquierdo
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                personaje.MoverDerecha(anchoVentana);
            }
            DibujarColeccionables(ventana.window);
            VerificarColisionesColeccionables();
            ventana.Mostrar();
        
            //manda llamar el metodo 
            puntaje.Dibujar(ventana.window, font, 10, 10);
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
        sf::Text titulo("CAT ROAD", fuente, 50);
        titulo.setFillColor(sf::Color::White);
        titulo.setPosition(250, 100);

        // Configurar las opciones del menú
        sf::Text opcionJugar("Presiona Enter para Jugar", fuente, 30);
        opcionJugar.setFillColor(sf::Color::White);
        opcionJugar.setPosition(200, 300);

        sf::Text opcionSalir("Presiona Esc para Salir", fuente, 30);
        opcionSalir.setFillColor(sf::Color::White);
        opcionSalir.setPosition(200, 400);

        while (ventana.isOpen()) {
            sf::Event evento;
            while (ventana.pollEvent(evento)) {
                if (evento.type == sf::Event::Closed) {
                    ventana.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
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
    }
};
