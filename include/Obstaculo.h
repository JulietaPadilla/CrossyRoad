#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Obstaculo {
private:
    std::string tipo;
    int gridX;
    int gridY;
    int direction; // 1: derecha, -1: izquierda
    sf::RectangleShape shape;
    sf::Texture textura;
    sf::Sprite sprite;
    bool activo;

public:
    Obstaculo(const std::string& t = "car", int x = 0, int y = 0, int dir = 1)
        : tipo(t), gridX(x), gridY(y), direction(dir), activo(true) {
        std::string rutaSprite;
        if (tipo == "bus") {
            rutaSprite = "assets/images/bus.png";
        } else if (tipo == "bus_school") {
            rutaSprite = "assets/images/bus_school.png";
        } else if (tipo == "ambulance") {
            rutaSprite = "assets/images/ambulance.png";
        } else if (tipo == "police") {
            rutaSprite = "assets/images/police.png";
        } else if (tipo == "sedan") {
            rutaSprite = "assets/images/sedan.png";
        } else if (tipo == "taxi") {
            rutaSprite = "assets/images/taxi.png";
        } else if (tipo == "truckdark") {
            rutaSprite = "assets/images/truckdark.png";
        } else if (tipo == "hotdog") {
            rutaSprite = "assets/images/hotdog.png";
        } else {
            rutaSprite = "assets/images/gato.png";
        }
        textura.loadFromFile(rutaSprite);
        sprite.setTexture(textura);
        sprite.setPosition(gridX * 48, gridY * 48);
        sprite.setScale(48.0f / textura.getSize().x, 48.0f / textura.getSize().y);
        shape.setSize(sf::Vector2f(48, 48));
        shape.setFillColor(sf::Color::Transparent);
        shape.setPosition(gridX * 48, gridY * 48);
    }

    void Mover(int maxGridX) {
        gridX += direction;
        if (gridX < 0) gridX = maxGridX;
        if (gridX > maxGridX) gridX = 0;
        shape.setPosition(gridX * 48, gridY * 48);
        sprite.setPosition(gridX * 48, gridY * 48);
    }

    int GetGridX() const { return gridX; }
    int GetGridY() const { return gridY; }
    int GetDirection() const { return direction; }
    sf::RectangleShape& GetShape() { return shape; }
    sf::Sprite& GetSprite() { return sprite; }
    bool EstaActivo() const { return activo; }
    void Destruir() { activo = false; }
    std::string GetTipo() const { return tipo; }
};
