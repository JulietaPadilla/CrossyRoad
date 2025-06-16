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
    bool activo;

public:
    Obstaculo(const std::string& t = "car", int x = 0, int y = 0, int dir = 1)
        : tipo(t), gridX(x), gridY(y), direction(dir), activo(true) {
        shape.setSize(sf::Vector2f(48, 48));
        shape.setFillColor(tipo == "car" ? sf::Color::Red : sf::Color::Blue);
        shape.setPosition(gridX * 48, gridY * 48);
    }

    void Mover(int maxGridX) {
        gridX += direction;
        if (gridX < 0) gridX = maxGridX;
        if (gridX > maxGridX) gridX = 0;
        shape.setPosition(gridX * 48, gridY * 48);
    }

    int GetGridX() const { return gridX; }
    int GetGridY() const { return gridY; }
    int GetDirection() const { return direction; }
    sf::RectangleShape& GetShape() { return shape; }
    bool EstaActivo() const { return activo; }
    void Destruir() { activo = false; }
};
