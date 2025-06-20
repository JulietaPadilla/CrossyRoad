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
    void EstablecerPosicion(int columna, int fila, int tamañoCelda = 48) {
        posicionX = columna * tamañoCelda;
        posicionY = fila * tamañoCelda;
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
    bool VerificarRecoleccion() const {
        return recolectado;
    }

    // Método para obtener el sprite (para colisiones)
    sf::Sprite* ObtenerSprite() {
        return &sprite;
    }

    int ObtenerValor() const { 
        return valor; 
    }

    std::string ObtenerTipo() const { 
        return tipo; 
    }

    // Método para reaparecer aleatoriamente en el grid
    void ReaparecerAleatorio(int columnaCuadricula, int filaCuadricula, int tamañoCelda, int columnaProhibida, int filaProhibida, const std::vector<std::pair<int,int>>& obstaculos) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distX(0, columnaCuadricula-1);
        std::uniform_int_distribution<int> distY(1, filaCuadricula-2); // Evita la fila 0 y la última
        int gx, gy;
        bool conflict;
        do {
            gx = distX(gen);
            gy = distY(gen);
            conflict = (gx == columnaProhibida && gy == filaProhibida);
            for (const auto& obs : obstaculos) {
                if (gx == obs.first && gy == obs.second) {
                    conflict = true;
                    break;
                }
            }
        } while (conflict);
        EstablecerPosicion(gx, gy, tamañoCelda);
        recolectado = false;
    }

    // Método para checar colisión con el jugador (en grid)
    bool ColisionarConGatito(int jugadorPosicionX, int jugadorPosicionY, int tamañoCelda = 48) {
        int gx = posicionX / tamañoCelda;
        int gy = posicionY / tamañoCelda;
        return (!recolectado && gx == jugadorPosicionX && gy == jugadorPosicionY);
    }
};

