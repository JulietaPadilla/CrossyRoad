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

        if (!fuente.loadFromFile("assets/fonts/1up.ttf")) {
            throw std::runtime_error("No se pudo cargar la fuente para el puntaje");
        }
        texto.setFont(fuente);
        texto.setCharacterSize(32);
        texto.setFillColor(sf::Color::White);
        texto.setOutlineColor(sf::Color::Black);
        texto.setOutlineThickness(2);
        texto.setPosition(20, 20);
        texto.setString("PUNTAJE: 0");
    }

    void Aumentar(int cantidad) {
        valor += cantidad;
        texto.setString("PUNTAJE: " + std::to_string(valor));
        if (valor > maximo) maximo = valor;
    }

    void Disminuir(int cantidad) {
        valor -= cantidad;
        if (valor < 0) valor = 0; // Evitar puntaje negativo
        texto.setString("PUNTAJE: " + std::to_string(valor));
    }

    void Reiniciar() { 
        valor = 0; 
        texto.setString("PUNTAJE: 0"); 
    }

    int ObtenerValor() const { 
        return valor; 
    }

    int ObtenerMaximo() const { 
        return maximo; 
    }

    void SetMaximo(int m) { 
        maximo = m; 
    }

    void GuardarMaximo(const std::string& archivo) {
        std::ofstream out("assets/puntajes/" + archivo);
        if (out) out << maximo;
    }

    void CargarMaximo(const std::string& archivo) {
        std::ifstream in("assets/puntajes/" + archivo);
        if (in) in >> maximo;
    }

    void Dibujar(sf::RenderWindow& window) { 
        window.draw(texto); 
    }
};
