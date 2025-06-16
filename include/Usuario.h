#pragma once
#include <string>

class Usuario {
private:
    std::string nombre;
    int puntuacionMaxima;

public:
    Usuario() : nombre(""), puntuacionMaxima(0) {}

    void IniciarSesion() {}
    int ObtenerPuntuacionMaxima() const { return puntuacionMaxima; }
};
