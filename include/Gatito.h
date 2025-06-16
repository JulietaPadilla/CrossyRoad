#pragma once
#include <string>
#include <SFML/Graphics/Rect.hpp> // Uso de sf::FloatRect
#include <SFML/Graphics.hpp> // Para sf::Texture y sf::Sprite

class Gatito {
private:
    std::string nombre;
    int posicionX;
    int posicionY;
    int vidas;
    int energia;
    sf::Texture textura;
    sf::Sprite sprite;

public:
    Gatito() : nombre("Gatito"), posicionX(0), posicionY(0), vidas(3), energia(100) {
        if (!textura.loadFromFile("assets/images/Grass_02.png")) {
            throw std::runtime_error("No se pudo cargar la textura del gatito");
        }
        sprite.setTexture(textura);
        sprite.setPosition(static_cast<float>(posicionX), static_cast<float>(posicionY)); // Posición inicial
    }

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
    void Mover(float offsetX, float offsetY) {
        sprite.move(offsetX, offsetY);
    }

    // Metodos Gestión de vidas y energía
    
    void PerderVida() {
        if (vidas > 0) vidas--;
    }
    int GetVidas() const {
        return vidas;
    }
    void GanarVida() { vidas++; }
    void ConsumirEnergia(int e) { energia -= e; }
    void RecargarEnergia(int e) { energia += e; }

    void SetPosicion(int x, int y) {
        posicionX = x;
        posicionY = y;
        sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
    }

    void Dibujar(sf::RenderWindow& ventana) {
        ventana.draw(sprite);
    }

    sf::Sprite* GetSprite() {
        return &sprite;
    }

    sf::FloatRect GetSpriteRect() const {
        return sf::FloatRect(static_cast<float>(posicionX), static_cast<float>(posicionY), 64.0f, 64.0f); // Suponiendo un tamaño de sprite de 64x64
    }

};
