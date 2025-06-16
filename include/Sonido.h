#pragma once
#include <string>

class Sonido {
private:
    std::string archivo;

public:
    Sonido() : archivo("") {}

    void Reproducir() {}
    void Detener() {}
};
