#include "mapa.h"
#include "pieza.h"
#include <cstdlib>
#include <random>
#include <termios.h>
#include <unistd.h>

// figuras
const int TAM = 8;
const int STRAIGHT[TAM] = { 0, 0, 1, 0, 2, 0, 3, 0 };
const int SQUARE[TAM] = { 0, 0, 1, 0, 0, 1, 1, 1 };
const int TE[TAM] = { 0, 0, 1, 0, 1, 1, 2, 0 };
const int ELE1[TAM] = { 0, 0, 1, 0, 2, 0, 2, 1 };
const int ELE2[TAM] = { 0, 0, 1, 0, 2, 0, 0, 1 };
const int SKEW1[TAM] = { 0, 1, 1, 1, 1, 0, 2, 0 };
const int SKEW2[TAM] = { 0, 0, 1, 1, 1, 0, 2, 1 };

void clear() { system("clear"); }

char getch()
{
    struct termios oldt, newt;
    char c;

    // Obtener la configuración actual del terminal
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Desactivar el modo de eco y el modo de canonización
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Leer un carácter
    c = getchar();

    // Restaurar la configuración original del terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

char** copiarMapa(Mapa mapa)
{
    char** display = mapa.getMapa();
    int altura = mapa.getAltura();
    int anchura = mapa.getAncura();
    char** copia = new char*[altura];

    for (int i = 0; i < altura; i++) {
        copia[i] = new char[anchura];
        for (int j = 0; j < anchura; j++)
            copia[i][j] = display[i][j];
    }

    return copia;
}

int* randomPieza()
{
    std::random_device rd; // semilla aleatoria
    std::mt19937 gen(rd()); // algoritmo generador
    std::uniform_int_distribution<> distrib(
        1, 8); // genera un número aleatorio del 1 al 8
    int* bloques = new int[TAM];

    switch (int aleatorio = distrib(gen)) {
    case 1:
        for (int i = 0; i < TAM; i++)
            bloques[i] = STRAIGHT[i];
        break;
    case 2:
        for (int i = 0; i < TAM; i++)
            bloques[i] = SQUARE[i];
        break;
    case 3:
        for (int i = 0; i < TAM; i++)
            bloques[i] = TE[i];
        break;
    case 4:
        for (int i = 0; i < TAM; i++)
            bloques[i] = ELE1[i];
        break;
    case 5:
        for (int i = 0; i < TAM; i++)
            bloques[i] = ELE2[i];
        break;
    case 6:
        for (int i = 0; i < TAM; i++)
            bloques[i] = SKEW1[i];
        break;
    case 7:
        for (int i = 0; i < TAM; i++)
            bloques[i] = SKEW2[i];
        break;
    }

    return bloques;
}

int main()
{
    Mapa mapa(14, 10);
    bool partida = true;
    char input;
    mapa.printMapa(mapa.getMapa()); // muestra el mapa
    while (partida) {
        int* coordenadas = randomPieza();
        Pieza pieza(coordenadas, mapa.getMedio());
        delete[] coordenadas; // liberar memoria de la pieza aleatoria despues de
                              // construirla

        bool colocado = false;
        while (!colocado) {
            input = getch(); // Llama a la función para leer un carácter

            switch (input) { // según el imput hace un acción con la pieza
            case 'A':
                pieza.girar();
                break;
            case 'B':
                pieza.izquierda();
                break;
            case 'D':
                pieza.derecha();
                break;
            case 'C':
                pieza.bajar();
                break;
            }
            mapa.actualizarMapa(pieza.getCoordenadas()); // actualiza el estado del mapa
            clear();
            char** copia = copiarMapa(mapa);
            mapa.printMapa(mapa.getMapa()); // muestra el mapa
            mapa.actualizarTodoMapa(copia);
        }
    }
    return 0;
}
