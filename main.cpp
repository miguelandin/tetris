#include "mapa.h"
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

// función para limpiar la consola
void clear() { system("clear"); }

// función para leer imputs
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

// genera una pieza aleatoria
const int* randomPieza()
{ // Return const int*
    static const int* shapes[] = { STRAIGHT, SQUARE, TE, ELE1, ELE2, SKEW1, SKEW2 };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 6);
    return shapes[distrib(gen)];
}

int main()
{
    // variables
    Pieza* piezaNueva = nullptr;
    Pieza* piezaAntigua = nullptr;
    Mapa mapa(14, 10);
    bool fin = false;

    mapa.printMapa();

    while (!fin) {
        piezaNueva = new Pieza(randomPieza(), mapa.getMedio());
        fin = mapa.hayColision(piezaNueva); // si no hay espacio, termina
        bool colocada = false;

        while (!colocada) {
            piezaAntigua = new Pieza(piezaNueva->getCoordenadas(), 0);
            bool abajo = piezaNueva->mover(getch());
            colocada = mapa.actualizarMapa(piezaNueva, piezaAntigua, abajo);
            delete piezaAntigua;
            piezaAntigua = nullptr;
            clear();
            mapa.printMapa();
        }
        mapa.limpiarLinea();
    }

    // liberar la memoria de los punteros
    delete piezaNueva;
    delete piezaAntigua;
    piezaAntigua = nullptr;
    piezaNueva = nullptr;
}
