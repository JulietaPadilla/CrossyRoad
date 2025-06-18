#include <SFML/Graphics.hpp>
#include <JuegoCatCross.h>
#include <Sonido.h>

int main() {
    Sonido musica;
    musica.reproducir(true); // Reproducir en loop

    JuegoCatCross juego;
    //juego.MostrarPantallaInicio(); // Mostrar la pantalla de inicio
    juego.IniciarJuego(); // Iniciar el juego principal
    return 0;
}