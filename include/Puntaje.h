#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

class Puntaje {
private:
    int valor;
    int maximo;

public:
    Puntaje() : valor(0), maximo(0) {}

    // Actualizar puntaje
    void Aumentar(int cantidad) { 
        valor += cantidad; 
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
    void Dibujar(sf::RenderWindow& window, sf::Font& font, int x = 10, int y = 10) {
        sf::Text texto;
        texto.setFont(font);
        texto.setString("Puntaje: " + std::to_string(valor) + "\nMaximo: " + std::to_string(maximo));
        texto.setCharacterSize(24);
        texto.setFillColor(sf::Color::Black);
        texto.setPosition(x, y);
        window.draw(texto);
    }
};
