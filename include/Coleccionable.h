#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Coleccionable {
private:
    std::string tipo;
    int posicionX;
    int posicionY;
    sf::Texture textura;
    sf::Sprite sprite;
    bool recolectado = false; // Indica si el coleccionable ha sido recolectado

public:
    Coleccionable() : tipo(""), posicionX(0), posicionY(0) {}

    // Método para cargar la textura desde un archivo
    bool CargarTextura(const std::string& rutaArchivo) {
        if (!textura.loadFromFile(rutaArchivo)) {
            return false;
        }
        sprite.setTexture(textura);
        return true;
    }

    // Método para establecer la posición del coleccionable
    void SetPosicion(int x, int y) {
        posicionX = x;
        posicionY = y;
        sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
    }

    // Método para dibujar el coleccionable en la ventana
    void Dibujar(sf::RenderWindow& ventana) {
        if (!recolectado) {
            ventana.draw(sprite);
        }
    }

    // Método para recolectar el coleccionable
    void Recolectar() {
        if (!recolectado) {
            recolectado = true;
            sprite.setPosition(-100.0f, -100.0f); // Hide sprite
        }
    }

    // Método para verificar si el coleccionable ha sido recolectado
    bool EsRecolectado() const {
        return recolectado;
    }

    // Método para obtener el sprite (para colisiones)
    sf::Sprite* GetSprite() {
        return &sprite;
    }

    // Método para actualizar el estado del coleccionable
    void Actualizar();

    // Método para renderizar el coleccionable
    void Renderizar(sf::RenderWindow& ventana) const;
};
