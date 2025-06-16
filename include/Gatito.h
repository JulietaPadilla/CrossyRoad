#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Gatito {
private:
    std::string nombre;
    int gridX;
    int gridY;
    int vidas;
    int energia;
    sf::Texture textura;
    sf::RectangleShape shape;

public:
    Gatito() : nombre("Gatito"), gridX(0), gridY(0), vidas(3), energia(100) {
        shape.setSize(sf::Vector2f(48, 48));
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(gridX * 48, gridY * 48);
    }

    void MoverArriba() { if (gridY > 0) gridY--; shape.setPosition(gridX * 48, gridY * 48); }
    void MoverAbajo(int maxGridY) { if (gridY < maxGridY) gridY++; shape.setPosition(gridX * 48, gridY * 48); }
    void MoverIzquierda() { if (gridX > 0) gridX--; shape.setPosition(gridX * 48, gridY * 48); }
    void MoverDerecha(int maxGridX) { if (gridX < maxGridX) gridX++; shape.setPosition(gridX * 48, gridY * 48); }

    int GetGridX() const { return gridX; }
    int GetGridY() const { return gridY; }
    sf::RectangleShape& GetShape() { return shape; }

    void Reiniciar(int startX, int startY) { gridX = startX; gridY = startY; shape.setPosition(gridX * 48, gridY * 48); }

    void PerderVida() { if (vidas > 0) vidas--; }
    int GetVidas() const { return vidas; }
    void SetVidas(int v) { vidas = v; }
};
