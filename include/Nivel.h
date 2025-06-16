#pragma once
#include <SFML/Graphics.hpp>
#include "Obstaculo.h"
#include <string>
#include <vector>

class Nivel {
private:
    std::string tema;
    std::vector<Obstaculo> obstaculos;
    int gridWidth;
    int gridHeight;

public:
    Nivel(int width = 10, int height = 10) : tema(""), gridWidth(width), gridHeight(height) {}

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

    std::vector<Obstaculo>& GetObstaculos() { return obstaculos; }
    int GetGridWidth() const { return gridWidth; }
    int GetGridHeight() const { return gridHeight; }
};
