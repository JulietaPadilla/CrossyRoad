#pragma once
#include <string>
#include <fstream>

class Usuario {
private:
    std::string nombre;
    int puntuacionMaxima;

public:
    Usuario() : nombre(""), puntuacionMaxima(0) {}

    void IniciarSesion() {}
    int ObtenerPuntuacionMaxima() const { return puntuacionMaxima; }
    void SetNombre(const std::string& n) { nombre = n; }
    std::string GetNombre() const { return nombre; }
    void GuardarPuntuacionMaxima(const std::string& archivo) {
        std::ofstream out(archivo);
        if (out) out << puntuacionMaxima;
    }
    void CargarPuntuacionMaxima(const std::string& archivo) {
        std::ifstream in(archivo);
        if (in) in >> puntuacionMaxima;
    }
    void SetPuntuacionMaxima(int p) { puntuacionMaxima = p; }
};
