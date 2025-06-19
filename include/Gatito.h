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
    sf::Sprite sprite;
    int currentFrame = 0;
    int numFrames = 4;
    int frameWidth = 32;
    int frameHeight = 32;
    sf::Clock animClock;
    float frameTime = 0.15f;
    sf::RectangleShape shape;

public:
    Gatito() : nombre("Gatito"), gridX(0), gridY(0), vidas(3), energia(100) {
        textura.loadFromFile("assets/images/obstaculo1.png");
        sprite.setTexture(textura);
        sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
        sprite.setScale(1.5f, 1.5f); // Ajusta la escala para 32x32 a 48x48
        sprite.setPosition(gridX * 48, gridY * 48);
        shape.setSize(sf::Vector2f(48, 48));
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(gridX * 48, gridY * 48);
    }

    void MoverArriba() { if (gridY > 0) gridY--; shape.setPosition(gridX * 48, gridY * 48); sprite.setPosition(gridX * 48, gridY * 48); }
    void MoverAbajo(int maxGridY) { if (gridY < maxGridY) gridY++; shape.setPosition(gridX * 48, gridY * 48); sprite.setPosition(gridX * 48, gridY * 48); }
    void MoverIzquierda() { if (gridX > 0) gridX--; shape.setPosition(gridX * 48, gridY * 48); sprite.setPosition(gridX * 48, gridY * 48); }
    void MoverDerecha(int maxGridX) { if (gridX < maxGridX) gridX++; shape.setPosition(gridX * 48, gridY * 48); sprite.setPosition(gridX * 48, gridY * 48); }

    int GetGridX() const { return gridX; }
    int GetGridY() const { return gridY; }
    sf::RectangleShape& GetShape() { return shape; }
    sf::Sprite& GetSprite() { return sprite; }

    void Reiniciar(int startX, int startY) { gridX = startX; gridY = startY; shape.setPosition(gridX * 48, gridY * 48); sprite.setPosition(gridX * 48, gridY * 48); }

    void PerderVida() { if (vidas > 0) vidas--; }
    int GetVidas() const { return vidas; }
    void SetVidas(int v) { vidas = v; }

    void ActualizarAnimacion() {
        if (animClock.getElapsedTime().asSeconds() >= frameTime) {
            currentFrame = (currentFrame + 1) % numFrames;
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            animClock.restart();
        }
    }

    void Dibujar(sf::RenderWindow& window) {
        sprite.setPosition(gridX * 48, gridY * 48);
        window.draw(sprite);
    }
};
