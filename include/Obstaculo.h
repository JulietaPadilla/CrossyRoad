#pragma once
#include <string>
#include <SFML/Graphics.hpp> // Asegúrate de incluir SFML/Graphics.hpp para la clase sf::RenderWindow

class Obstaculo {
private:
    std::string tipo;
    int posicionX;
    int posicionY;
    int ancho;
    int alto;
    bool activo;

public:
    // Constructor por defecto: crea un obstáculo inactivo en la posición (0,0) con tamaño 1x1
    Obstaculo() : tipo(""), posicionX(0), posicionY(0), ancho(1), alto(1), activo(true) {}
    // Constructor personalizado: permite crear un obstáculo con tipo, posición y tamaño específicos
    Obstaculo(const std::string& t, int x, int y, int w, int h)
        : tipo(t), posicionX(x), posicionY(y), ancho(w), alto(h), activo(true) {}

    // Cambia la posición del obstáculo en el escenario
    void setPosicion(int x, int y) { posicionX = x; posicionY = y; }
    // Devuelve la posición X del obstáculo
    int getPosicionX() const { return posicionX; }
    // Devuelve la posición Y del obstáculo
    int getPosicionY() const { return posicionY; }
    // Cambia el tipo de obstáculo (por ejemplo: roca, árbol, etc.)
    void setTipo(const std::string& t) { tipo = t; }
    // Devuelve el tipo de obstáculo
    std::string getTipo() const { return tipo; }
    // Cambia el tamaño del obstáculo
    void setTamano(int w, int h) { ancho = w; alto = h; }
    // Devuelve el ancho del obstáculo
    int getAncho() const { return ancho; }
    // Devuelve el alto del obstáculo
    int getAlto() const { return alto; }
    // Indica si el obstáculo está activo en el juego
    bool estaActivo() const { return activo; }
    // Desactiva el obstáculo (por ejemplo, si es destruido o recogido)
    void destruir() { activo = false; }
    // Verifica si el obstáculo colisiona con un área dada (útil para detectar choques con el jugador u otros objetos)
    bool colisionaCon(int x, int y, int w, int h) const {
        return activo &&
            posicionX < x + w &&
            posicionX + ancho > x &&
            posicionY < y + h &&
            posicionY + alto > y;
    }
    // Método para mover el obstáculo (puede ser redefinido para obstáculos móviles)
    void Mover() {}

    // Método para actualizar el estado del obstáculo
    void Actualizar();

    // Método para renderizar el obstáculo
    void Renderizar(sf::RenderWindow& ventana) const;
};
