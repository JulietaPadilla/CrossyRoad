#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

class Obstaculo {
private:
    std::string tipo;
    int gridX;
    int gridY;
    int direction; // 1: derecha, -1: izquierda
    int largo;
    sf::RectangleShape shape;
    bool activo;
    sf::Sprite sprite;
    bool texturaCargada;
    static std::map<int, sf::Texture> texturasCompartidas;

public:
    Obstaculo(const std::string& t = "car", int x = 0, int y = 0, int dir = 1, int large=1)
        : tipo(t), gridX(x), gridY(y), direction(dir), largo(large), activo(true), texturaCargada(false) {
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
            sprite.setPosition(gridX * 48, gridY * 48);
            sf::Vector2u texSize = texturasCompartidas[largo].getSize();
            if (texSize.x != static_cast<unsigned int>(48 * largo) || texSize.y != 48u) {
                float scaleX = (48.0f * largo) / static_cast<float>(texSize.x);
                float scaleY = 48.0f / static_cast<float>(texSize.y);
                sprite.setScale(scaleX, scaleY);
            }
            texturaCargada = true;
        } else {
            shape.setSize(sf::Vector2f(48 * largo, 48));
            shape.setFillColor(sf::Color(200, 50, 50, 180));
            shape.setOutlineThickness(2);
            shape.setOutlineColor(sf::Color::Black);
            shape.setPosition(gridX * 48, gridY * 48);
            texturaCargada = false;
        }
    }

    void Mover(int maxGridX) {
        gridX += direction;
        if (gridX < 0) gridX = maxGridX;
        if (gridX > maxGridX) gridX = 0;
        shape.setPosition(gridX * 48, gridY * 48);
        sprite.setPosition(gridX * 48, gridY * 48);
    }

    void Dibujar(sf::RenderWindow& window) {
        if (texturaCargada) {
            window.draw(sprite);
            // Dibuja un borde para visualizar el área del obstáculo
            sf::RectangleShape borde(sf::Vector2f(48 * largo, 48));
            borde.setPosition(gridX * 48, gridY * 48);
            borde.setFillColor(sf::Color::Transparent);
            borde.setOutlineThickness(2);
            borde.setOutlineColor(sf::Color::Yellow);
            window.draw(borde);
        } else {
            window.draw(shape);
        }
    }

    int GetGridX() const { return gridX; }
    int GetGridY() const { return gridY; }
    int GetDirection() const { return direction; }
    int GetLargo() const { return largo; }
    sf::RectangleShape& GetShape() { return shape; }
    sf::Sprite& GetSprite() { return sprite; }
    bool EstaActivo() const { return activo; }
    void Destruir() { activo = false; }
};

std::map<int, sf::Texture> Obstaculo::texturasCompartidas;

