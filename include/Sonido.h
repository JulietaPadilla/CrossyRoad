#pragma once
#include <string>
#include <SFML/Audio.hpp>

class Sonido {
private:
    std::string archivo;
    sf::Music musica;
    bool cargado;

public:
    Sonido() : archivo("assets/Music/musica.mp3"), cargado(false) {
        Cargar(archivo);
    }

    Sonido(const std::string& archivo_) : archivo(archivo_), cargado(false) {
        Cargar(archivo_);
    }

    bool Cargar(const std::string& archivo_) {
        archivo = archivo_;
        cargado = musica.openFromFile(archivo);
        return cargado;
    }

    void Reproducir(bool loop = false) {
        if (cargado) {
            musica.setLoop(loop);
            musica.play();
        }
    }

    void Detener() {
        if (cargado) {
            musica.stop();
        }
    }

    bool ObtenerEstadoReproduccion() const {
        return cargado && musica.getStatus() == sf::Music::Playing;
    }
};
