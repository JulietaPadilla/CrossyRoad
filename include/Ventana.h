#pragma once

#include <SFML/Graphics.hpp>
#include <string>

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
    void Mostrar() {
        window.clear();
        window.draw(sprite);
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

    bool EstaAbierta() const {
        return window.isOpen();
    }
};
