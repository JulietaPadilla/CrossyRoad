#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Ventana {
private:
    int ancho;
    int alto;
    sf::Texture textura;
    sf::Sprite sprite;

public:
    sf::RenderWindow window;

    Ventana() : ancho(800), alto(600), window(sf::VideoMode(ancho, alto), "Juego") {}

    // Carga una imagen desde la ruta especificada
    bool CargarImagen(const std::string& rutaImagen) {
        if (!textura.loadFromFile("assets/images/Grass_02.png")) {
            return false;
        }
        sprite.setTexture(textura);
        return true;
    }

    // Muestra la imagen cargada en la ventana
    void MostrarElementos(const std::vector<sf::Drawable*>& elementos) {
        window.clear();
        for (const auto& elemento : elementos) {
            window.draw(*elemento);
        }
        window.display();
    }

    void ManejarEventos() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    void Limpiar() {
        window.clear();
    }

    bool EstaAbierta() const {
        return window.isOpen();
    }

    void DibujarElemento(const sf::Drawable& elemento) {
        window.draw(elemento);
    }
};
