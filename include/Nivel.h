#pragma once
#include <SFML/Graphics.hpp>
#include <Obstaculo.h>
#include <Coleccionable.h>
#include <string>
#include <vector>
#include <iostream> 

class Nivel {
private:
    std::string tema;
    std::vector<Obstaculo> obstaculos;
    std::vector<Coleccionable> coleccionables;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
    Nivel() : tema("") {}

    void GenerarObstaculos() {
        obstaculos.clear();
        for (int i = 0; i < 5; ++i) {
            Obstaculo obstaculo;
            obstaculos.push_back(obstaculo);
        }
    }

    void GenerarColeccionables() {
        coleccionables.clear();
        for (int i = 0; i < 3; ++i) {
            Coleccionable coleccionable;
            coleccionables.push_back(coleccionable);
        }
    }

    void Actualizar() {
        for (auto& obstaculo : obstaculos) {
            obstaculo.Actualizar();
        }
        for (auto& coleccionable : coleccionables) {
            coleccionable.Actualizar();
        }
    }

    void Renderizar(sf::RenderWindow& ventana) {
        ventana.draw(backgroundSprite);
        for (const auto& obstaculo : obstaculos) {
            obstaculo.Renderizar(ventana);
        }
        for (const auto& coleccionable : coleccionables) {
            coleccionable.Renderizar(ventana);
        }
    }

    void CargarRecursos(const std::string& rutaFondo) {
        if (!backgroundTexture.loadFromFile("assets/images/fondo_inicio.png")) {
            std::cerr << "Error al cargar la textura del fondo desde: " << rutaFondo << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);
    }
};
