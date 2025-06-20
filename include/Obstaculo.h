#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

class Obstaculo {
private:
    std::string tipo;
    int columna;
    int fila;
    int direccion; // 1: derecha, -1: izquierda
    int largo;
    sf::RectangleShape forma;
    bool activo;
    sf::Sprite sprite;
    bool texturaCargada;
    static std::map<int, sf::Texture> texturasCompartidas;

public:
    Obstaculo(const std::string& t = "car", int x = 0, int y = 0, int dir = 1, int large=1)
        : tipo(t), columna(x), fila(y), direccion(dir), largo(large), activo(true), texturaCargada(false) {
        std::string ruta = "assets/images/obstaculo" + std::to_string(largo) + ".png";
        // Cargar textura solo una vez por largo
        auto it = texturasCompartidas.find(largo);
        if (it == texturasCompartidas.end()) {
            sf::Texture tex;
            if (tex.loadFromFile(ruta)) {
                texturasCompartidas[largo] = tex;
            } else {
                std::cerr << "[Obstaculo] No se pudo cargar la textura: " << ruta << std::endl;
            }
        }
        if (texturasCompartidas.count(largo)) {
            sprite.setTexture(texturasCompartidas[largo]);
            sprite.setPosition(columna * 48, fila * 48);
            sf::Vector2u texSize = texturasCompartidas[largo].getSize();
            if (texSize.x != static_cast<unsigned int>(48 * largo) || texSize.y != 48u) {
                float escalaX = (48.0f * largo) / static_cast<float>(texSize.x);
                float escalaY = 48.0f / static_cast<float>(texSize.y);
                sprite.setScale(escalaX, escalaY);
            }
            texturaCargada = true;
        } else {
            forma.setSize(sf::Vector2f(48 * largo, 48));
            forma.setFillColor(sf::Color(200, 50, 50, 180));
            forma.setOutlineThickness(2);
            forma.setOutlineColor(sf::Color::Black);
            forma.setPosition(columna * 48, fila * 48);
            texturaCargada = false;
        }
    }

    void Mover(int maximaColumna) {
        columna += direccion;
        if (columna < 0) columna = maximaColumna;
        if (columna > maximaColumna) columna = 0;
        forma.setPosition(columna * 48, fila * 48);
        sprite.setPosition(columna * 48, fila * 48);
    }

    void Dibujar(sf::RenderWindow& window) {
        if (texturaCargada) {
            window.draw(sprite);
            // Dibuja un borde para visualizar el área del obstáculo
            sf::RectangleShape borde(sf::Vector2f(48 * largo, 48));
            borde.setPosition(columna * 48, fila * 48);
            borde.setFillColor(sf::Color::Transparent);
            borde.setOutlineThickness(2);
            borde.setOutlineColor(sf::Color::Yellow);
            window.draw(borde);
        } else {
            window.draw(forma);
        }
    }

    int ObtenerColumna() const { 
        return columna; 
    }

    int ObtenerFila() const { 
        return fila; 
    }

    int ObtenerDireccion() const { 
        return direccion; 
    }

    int ObtenerLargo() const { 
        return largo; 
    }

    sf::RectangleShape& ObtenerForma() { 
        return forma; 
    }

    sf::Sprite& ObtenerSprite() { 
        return sprite; 
    }

    bool ObtenerEstadoActivo() const { 
        return activo; 
    }

    void Destruir() { 
        activo = false; 
    }
};

std::map<int, sf::Texture> Obstaculo::texturasCompartidas;

