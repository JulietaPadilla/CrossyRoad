#pragma once
#include <string>
#include <SFML/Audio.hpp>

class Sonido {
private:
    std::string archivo;
    sf::Music music;
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
        cargado = music.openFromFile(archivo);
        return cargado;
    }

    void Reproducir(bool loop = false) {
        if (cargado) {
            music.setLoop(loop);
            music.play();
        }
    }

    void Detener() {
        if (cargado) {
            music.stop();
        }
    }

    bool EstaReproduciendo() const {
        return cargado && music.getStatus() == sf::Music::Playing;
    }
};
