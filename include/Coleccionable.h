#pragma once
#include <string>
#include <SFML/Graphics.hpp>

#include <random>

class Coleccionable {
private:
    std::string tipo;
    int posicionX;
    int posicionY;
    sf::Texture textura;
    sf::Sprite sprite;
    bool recolectado = false; // Indica si el coleccionable ha sido recolectado
    int valor = 0; // Valor de la moneda (5 o 10)

public:
    Coleccionable() : tipo(""), posicionX(0), posicionY(0) {}
    Coleccionable(const std::string& tipo_, int valor_) : tipo(tipo_), posicionX(0), posicionY(0), valor(valor_) {}

    // Método para cargar la textura desde un archivo
    bool CargarTextura(const std::string& rutaArchivo) {
        if (!textura.loadFromFile(rutaArchivo)) {
            return false;
        }
        sprite.setTexture(textura);
        return true;
    }

    // Método para establecer la posición del coleccionable en coordenadas de cuadrícula
    void SetPosicionGrid(int gridX, int gridY, int cellSize = 48) {
        posicionX = gridX * cellSize;
        posicionY = gridY * cellSize;
        sprite.setPosition(static_cast<float>(posicionX), static_cast<float>(posicionY));
    }

    // Método para dibujar el coleccionable en la ventana
    void Dibujar(sf::RenderWindow& ventana) {
        if (!recolectado) {
            ventana.draw(sprite);
        }
    }

    // Método para recolectar el coleccionable
    void Recolectar() {
        if (!recolectado) {
            recolectado = true;
            sprite.setPosition(-100.0f, -100.0f); // Hide sprite
        }
    }

    // Método para verificar si el coleccionable ha sido recolectado
    bool EsRecolectado() const {
        return recolectado;
    }

    // Método para obtener el sprite (para colisiones)
    sf::Sprite* GetSprite() {
        return &sprite;
    }

    int GetValor() const { return valor; }
    std::string GetTipo() const { return tipo; }

    // Método para reaparecer aleatoriamente en el grid
    void ReaparecerAleatorio(int gridCols, int gridRows, int cellSize, int avoidX, int avoidY, const std::vector<std::pair<int,int>>& obstaculos) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distX(0, gridCols-1);
        std::uniform_int_distribution<int> distY(1, gridRows-2); // Evita la fila 0 y la última
        int gx, gy;
        bool conflict;
        do {
            gx = distX(gen);
            gy = distY(gen);
            conflict = (gx == avoidX && gy == avoidY);
            for (const auto& obs : obstaculos) {
                if (gx == obs.first && gy == obs.second) {
                    conflict = true;
                    break;
                }
            }
        } while (conflict);
        SetPosicionGrid(gx, gy, cellSize);
        recolectado = false;
    }

    // Método para checar colisión con el jugador (en grid)
    bool ColisionaCon(int playerGridX, int playerGridY, int cellSize = 48) {
        int gx = posicionX / cellSize;
        int gy = posicionY / cellSize;
        return (!recolectado && gx == playerGridX && gy == playerGridY);
    }
};

