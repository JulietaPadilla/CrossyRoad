#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Gatito {
private:
    std::string nombre;
    int columna;
    int fila;
    int vida;
    sf::Texture textura;
    sf::Sprite sprite;
    int actualFrame = 0;
    int numeroFrames = 7;
    int anchoFrame = 32;
    int altoFrame = 32;
    sf::Clock relojAnimacion;
    float tiempoFrame = 0.15f;
    sf::RectangleShape forma;

public:
    Gatito() : nombre("Gatito"), columna(0), fila(0), vida(1) {
        textura.loadFromFile("assets/images/PirateCat1.png");
        sprite.setTexture(textura);
        sprite.setTextureRect(sf::IntRect(0, 0, anchoFrame, altoFrame));
        sprite.setScale(1.5f, 1.5f); // Ajusta la escala para 32x32 a 48x48
        sprite.setPosition(columna * 48, fila * 48);
        forma.setSize(sf::Vector2f(48, 48));
        forma.setFillColor(sf::Color::Yellow);
        forma.setPosition(columna * 48, fila * 48);
    }

    void MoverArriba() { 
        if (fila > 0) fila--; 
        forma.setPosition(columna * 48, fila * 48); 
        sprite.setPosition(columna * 48, fila * 48); 
    }

    void MoverAbajo(int filaMaxima) { 
        if (fila < filaMaxima) fila++; 
        forma.setPosition(columna * 48, fila * 48); 
        sprite.setPosition(columna * 48, fila * 48); 
    }

    void MoverIzquierda() { 
        if (columna > 0) columna--; 
        forma.setPosition(columna * 48, fila * 48); 
        sprite.setPosition(columna * 48, fila * 48); 
    }

    void MoverDerecha(int columnaMaxima) { 
        if (columna < columnaMaxima) columna++; 
        forma.setPosition(columna * 48, fila * 48); 
        sprite.setPosition(columna * 48, fila * 48); 
    }

    int ObtenerColumna() const { 
        return columna; 
    }

    int ObtenerFila() const { 
        return fila; 
    }

    sf::RectangleShape& ObtenerForma() { 
        return forma; 
    }

    sf::Sprite& ObtenerSprite() { 
        return sprite; 
    }

    void Reiniciar(int columnaInicio, int filaInicio) { 
        columna = columnaInicio; 
        fila = filaInicio; 
        forma.setPosition(columna * 48, fila * 48); 
        sprite.setPosition(columna * 48, fila * 48); 
    }

    void PerderVida() { 
        if (vida > 0) vida--; 
    }

    void ActualizarAnimacion() {
        if (relojAnimacion.getElapsedTime().asSeconds() >= tiempoFrame) {
            actualFrame = (actualFrame + 1) % numeroFrames;
            sprite.setTextureRect(sf::IntRect(actualFrame * anchoFrame, 0, anchoFrame, altoFrame));
            relojAnimacion.restart();
        }
    }

    void Dibujar(sf::RenderWindow& window) {
        sprite.setPosition(columna * 48, fila * 48);
        window.draw(sprite);
    }
};
