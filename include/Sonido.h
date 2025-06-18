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
        cargar(archivo);
    }
    Sonido(const std::string& archivo_) : archivo(archivo_), cargado(false) {
        cargar(archivo_);
    }

    bool cargar(const std::string& archivo_) {
        archivo = archivo_;
        cargado = music.openFromFile(archivo);
        return cargado;
    }

    void reproducir(bool loop = false) {
        if (cargado) {
            music.setLoop(loop);
            music.play();
        }
    }

    void detener() {
        if (cargado) {
            music.stop();
        }
    }

    bool estaReproduciendo() const {
        return cargado && music.getStatus() == sf::Music::Playing;
    }
};
