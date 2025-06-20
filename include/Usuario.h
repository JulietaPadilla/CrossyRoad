#pragma once
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <iostream>

class Usuario {
private:
    std::string nombre;
    int puntuacionMaxima;

public:
    Usuario() : nombre(""), puntuacionMaxima(0) {}

    void GuardarPuntuacionMaxima(const std::string& archivo) {
        // Solo usa el nombre de archivo, no agregues la ruta aquí
        std::ofstream out("assets/puntajes/" + archivo);
        if (!out) {
            std::cerr << "[Usuario] Error: No se pudo abrir el archivo de puntaje para guardar: " << archivo << std::endl;
        } else {
            out << puntuacionMaxima;
            out.close();
        }
    }
    void CargarPuntuacionMaxima(const std::string& archivo) {
        std::ifstream in("assets/puntajes/" + archivo);
        if (!in) {
            puntuacionMaxima = 0;
        } else {
            in >> puntuacionMaxima;
            in.close();
        }
    }
    void ConfigurarPuntuacionMaxima(int p) { puntuacionMaxima = p; }
    void ConfigurarNombre(const std::string& n) { nombre = n; }
    std::string ObtenerNombre() const { return nombre; }
    int ObtenerPuntuacionMaxima() const { return puntuacionMaxima; }
};
