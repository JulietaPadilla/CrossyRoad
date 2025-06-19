#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Obstaculo {
private:
    std::string tipo;
    int gridX;
    int gridY;
    int direction; // 1: derecha, -1: izquierda
    int largo;
    sf::RectangleShape shape;
    bool activo;

public:
    Obstaculo(const std::string& t = "car", int x = 0, int y = 0, int dir = 1, int large=1)
        : tipo(t), gridX(x), gridY(y), direction(dir),largo(large), activo(true) {
        shape.setSize(sf::Vector2f(48 * largo, 48));
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
    int GetLargo() const { return largo; }
    bool EstaActivo() const { return activo; }
    void Destruir() { activo = false; }
};
