#pragma once
#include <SFML/Graphics.hpp>
#include <Obstaculo.h>
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
        std::uniform_real_distribution<float> velDist(0.18f, 0.32f);
        std::uniform_int_distribution<int> skipDist(0, 4);
        // 0: bus, 1: bus_school, 2: ambulance, 3: police, 4: sedan, 5: taxi, 6: truckdark, 7: hotdog
        std::uniform_int_distribution<int> tipoDist(0, 7);
        int separacionMin = std::max(2, 4 + nivel / 3);
        int separacionMax = std::max(separacionMin, 5 + nivel / 2);
        std::uniform_int_distribution<int> sepDist(separacionMin, separacionMax);
        int direction = 1; // Todos los obstáculos van a la derecha
        for (int fila = 1; fila < gridHeight - 1; ++fila) {
            bool tieneObstaculos = (rand() % 2 == 0);
            filaConObstaculos[fila] = tieneObstaculos;
            velocidadesPorFila[fila] = velDist(gen);
            temporizadoresPorFila[fila].restart();
            if (!tieneObstaculos) continue;
            int maxObstaculos = std::max(1, gridWidth / (separacionMin + 1));
            int cantidadRandom = 2 + (nivel / 3);
            if (maxObstaculos < 1) maxObstaculos = 1;
            if (cantidadRandom < 1) cantidadRandom = 1;
            int cantidadExtra = gen() % 2;
            int cantidadTmp = cantidadRandom + cantidadExtra;
            int cantidad = (maxObstaculos < cantidadTmp) ? maxObstaculos : cantidadTmp;
            int separacion = std::max(8, sepDist(gen) + (rand() % 4));
            int start = gen() % gridWidth;
            for (int i = 0; i < cantidad; ++i) {
                int x = (start + i * separacion) % gridWidth;
                std::string tipo;
                int tipoNum = tipoDist(gen);
                if (tipoNum == 0) tipo = "bus";
                else if (tipoNum == 1) tipo = "bus_school";
                else if (tipoNum == 2) tipo = "ambulance";
                else if (tipoNum == 3) tipo = "police";
                else if (tipoNum == 4) tipo = "sedan";
                else if (tipoNum == 5) tipo = "taxi";
                else if (tipoNum == 6) tipo = "truckdark";
                else tipo = "hotdog";
                obstaculos.emplace_back(tipo, x, fila, direction);
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
