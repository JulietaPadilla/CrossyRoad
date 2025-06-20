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
    int anchoCuadricula;
    int altoCuadricula;
    std::vector<float> velocidadesPorFila; // velocidad de cada fila
    std::vector<sf::Clock> temporizadoresPorFila; // temporizador de cada fila
    std::vector<bool> filaConObstaculos; // si la fila tiene obstáculos

public:
    Nivel(int ancho = 10, int alto = 10) : tema(""), anchoCuadricula(ancho), altoCuadricula(alto) {
        velocidadesPorFila.resize(alto, 0.25f);
        temporizadoresPorFila.resize(alto);
        filaConObstaculos.resize(alto, false);
    }

    void GenerarObstaculos(int fila, int cantidad, int direccion) {
        obstaculos.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> largoDist(1, 3); // tamaño aleatorio entre 1 y 3
        for (int i = 0; i < cantidad; ++i) {
            int x = i * (anchoCuadricula / cantidad);
            int largo = largoDist(gen);
            obstaculos.emplace_back("car", x, fila, direccion, largo);
        }
    }

    void ActualizarObstaculos() {
        for (auto& obs : obstaculos) {
            obs.Mover(anchoCuadricula - 1);
        }
    }

    void GenerarObstaculosAvanzado(int nivel) {
        obstaculos.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> velDist(0.18f, 0.32f); // velocidad más variada
        std::uniform_int_distribution<int> skipDist(0, 4); // 1 de cada 5 filas vacía (menos filas vacías)
        std::uniform_int_distribution<int> dirDist(0, 1);
        std::uniform_int_distribution<int> largoDist(1, 3); // tamaño aleatorio entre 1 y 3
        // Separación mínima y máxima más baja para más dificultad
        int separacionMin = std::max(2, 4 + nivel / 3); // nunca menos de 2
        int separacionMax = std::max(separacionMin, 5 + nivel / 2); // Asegura que separacionMax >= separacionMin
        std::uniform_int_distribution<int> sepDist(separacionMin, separacionMax);
        for (int fila = 1; fila < altoCuadricula - 1; ++fila) {
            // Más dispersión y aleatoriedad: 50% chance de fila vacía
            bool tieneObstaculos = (rand() % 2 == 0);
            filaConObstaculos[fila] = tieneObstaculos;
            velocidadesPorFila[fila] = velDist(gen);
            temporizadoresPorFila[fila].restart();
            if (!tieneObstaculos) continue;
            int direction = dirDist(gen) == 0 ? 1 : -1;
            int maxObstaculos = std::max(1, anchoCuadricula / (separacionMin + 1));
            int cantidadRandom = 2 + (nivel / 3);
            if (maxObstaculos < 1) maxObstaculos = 1;
            if (cantidadRandom < 1) cantidadRandom = 1;
            int cantidadExtra = gen() % 2;
            int cantidadTmp = cantidadRandom + cantidadExtra;
            int cantidad = (maxObstaculos < cantidadTmp) ? maxObstaculos : cantidadTmp;
            int separacion = std::max(8, sepDist(gen) + (rand() % 4));
            int start = gen() % anchoCuadricula;
            for (int i = 0; i < cantidad; ++i) {
                int x = (start + i * separacion) % anchoCuadricula;
                int largo = largoDist(gen);
                obstaculos.emplace_back("car", x, fila, direction, largo);
            }
        }
    }

    void ActualizarObstaculosAvanzado() {
        for (int fila = 1; fila < altoCuadricula - 1; ++fila) {
            if (!filaConObstaculos[fila]) continue;
            if (temporizadoresPorFila[fila].getElapsedTime().asSeconds() > velocidadesPorFila[fila]) {
                for (auto& obs : obstaculos) {
                    if (obs.ObtenerFila() == fila) {
                        obs.Mover(anchoCuadricula - 1);
                    }
                }
                temporizadoresPorFila[fila].restart();
            }
        }
    }

    std::vector<Obstaculo>& ObtenerObstaculos() { 
        return obstaculos; 
    }

    int ObtenerAnchoCuadricula() const { 
        return anchoCuadricula; 
    }

    int ObtenerAltoCuadricula() const { 
        return altoCuadricula; 
    }
};
