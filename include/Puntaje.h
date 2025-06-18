#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream> // Incluir para mensajes de depuración

class Puntaje {
private:
    int valor;
    int maximo;
    sf::Font fuente;
    sf::Text texto;

public:
    Puntaje() : valor(0), maximo(0) {
        if (!fuente.loadFromFile("assets/fonts/Platinum Sign.ttf")) {
            throw std::runtime_error("No se pudo cargar la fuente para el puntaje");
        }
        texto.setFont(fuente);
        texto.setCharacterSize(32); // Aumenta el tamaño de la letra
        texto.setFillColor(sf::Color::White);
        texto.setOutlineColor(sf::Color::Black); // Añade borde negro
        texto.setOutlineThickness(2); // Grosor del borde
        texto.setPosition(20, 20); // Posición más visible
        texto.setString("PUNTAJE: 0"); // Inicializa el texto
    }

    // Actualizar puntaje
    void Aumentar(int cantidad) { 
        valor += cantidad; 
        texto.setString("PUNTAJE: " + std::to_string(valor));
        if (valor > maximo) maximo = valor;
    }
    void Reiniciar() { valor = 0; }
    int ObtenerValor() const { return valor; }
    int ObtenerMaximo() const { return maximo; }

    // Guardar y cargar puntaje más alto
    void GuardarMaximo(const std::string& archivo) {
        std::ofstream out(archivo);
        if (out) out << maximo;
    }
    void CargarMaximo(const std::string& archivo) {
        std::ifstream in(archivo);
        if (in) in >> maximo;
    }

    // Mostrar puntaje en pantalla con SFML
    void Dibujar(sf::RenderWindow& window) {
        window.draw(texto);
    }
};
