#pragma once
#include <string>
#include <SFML/Graphics/Rect.hpp> // Uso de sf::FloatRect

class Gatito {
private:
    std::string nombre;
    int posicionX;
    int posicionY;
    int vidas;
    int energia;

public:
    Gatito() : nombre("Gatito"), posicionX(0), posicionY(0), vidas(3), energia(100) {}

    // Métodos de movimiento con límites de movimiento en la ventana
    void MoverArriba(int limiteSuperior = 0) {
        if (posicionY - 10 >= limiteSuperior)
            posicionY -= 10;
    }
    void MoverAbajo(int altoVentana, int altoSprite = 64) {
        if (posicionY + 10 <= altoVentana - altoSprite)
            posicionY += 10;
    }
    void MoverIzquierda(int limiteIzquierdo = 0) {
        if (posicionX - 10 >= limiteIzquierdo)
            posicionX -= 10;
    }
    void MoverDerecha(int anchoVentana, int anchoSprite = 64) {
        if (posicionX + 10 <= anchoVentana - anchoSprite)
            posicionX += 10;
    }

    // Metodos Gestión de vidas y energía
    
    void perderVida() { if (vidas > 0) vidas--; }
    void ganarVida() { vidas++; }
    void consumirEnergia(int e) { energia -= e; }
    void recargarEnergia(int e) { energia += e; }

    sf::FloatRect getSprite() const {
        return sf::FloatRect(static_cast<float>(posicionX), static_cast<float>(posicionY), 64.0f, 64.0f); // Suponiendo un tamaño de sprite de 64x64
    }

};
