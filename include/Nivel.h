#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculo.h"
#include <string>
#include <vector>
#include <random>

class Nivel {
private:
    std::string tema;
    std::vector<Obstaculo> obstaculos;
    int gridWidth;
    int gridHeight;
    std::vector<float> velocidadesPorFila; // velocidad de cada fila
    std::vector<sf::Clock> temporizadoresPorFila; // temporizador de cada fila
    std::vector<bool> filaConObstaculos; // si la fila tiene obstáculos

public:
    Nivel(int width = 10, int height = 10) : tema(""), gridWidth(width), gridHeight(height) {
        velocidadesPorFila.resize(height, 0.25f);
        temporizadoresPorFila.resize(height);
        filaConObstaculos.resize(height, false);
    }

    void GenerarObstaculos(int fila, int cantidad, int direction) {
        obstaculos.clear();
        for (int i = 0; i < cantidad; ++i) {
            int x = i * (gridWidth / cantidad);
            obstaculos.emplace_back("car", x, fila, direction);
        }
    }

    void ActualizarObstaculos() {
        for (auto& obs : obstaculos) {
            obs.Mover(gridWidth - 1);
        }
    }

    void GenerarObstaculosAvanzado(int nivel) {
        obstaculos.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> velDist(0.22f, 0.38f); // velocidad más baja (más lento)
        std::uniform_int_distribution<int> skipDist(0, 3); // 1 de cada 4 filas vacía
        std::uniform_int_distribution<int> dirDist(0, 1);
        std::uniform_int_distribution<int> sepDist(4, 6); // separación mayor
        for (int fila = 1; fila < gridHeight - 1; ++fila) {
            bool tieneObstaculos = skipDist(gen) != 0; // 75% chance de tener obstáculos
            filaConObstaculos[fila] = tieneObstaculos;
            velocidadesPorFila[fila] = velDist(gen);
            temporizadoresPorFila[fila].restart();
            if (!tieneObstaculos) continue;
            int direction = dirDist(gen) == 0 ? 1 : -1;
            int maxObstaculos = std::max(1, gridWidth / 3); // nunca más de un tercio de la fila
            int cantidad = std::min(maxObstaculos, 2 + (nivel / 2)); // menos obstáculos por fila
            int separacion = sepDist(gen);
            int start = gen() % gridWidth;
            for (int i = 0; i < cantidad; ++i) {
                int x = (start + i * separacion) % gridWidth;
                obstaculos.emplace_back("car", x, fila, direction);
            }
        }
    }

    void ActualizarObstaculosAvanzado() {
        for (int fila = 1; fila < gridHeight - 1; ++fila) {
            if (!filaConObstaculos[fila]) continue;
            if (temporizadoresPorFila[fila].getElapsedTime().asSeconds() > velocidadesPorFila[fila]) {
                for (auto& obs : obstaculos) {
                    if (obs.GetGridY() == fila) {
                        obs.Mover(gridWidth - 1);
                    }
                }
                temporizadoresPorFila[fila].restart();
            }
        }
    }

    std::vector<Obstaculo>& GetObstaculos() { return obstaculos; }
    int GetGridWidth() const { return gridWidth; }
    int GetGridHeight() const { return gridHeight; }
};
