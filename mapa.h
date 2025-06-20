#include "pieza.h"
#include <cstdlib>
#include <termios.h>
#include <unistd.h>

class Mapa {
    char** mapa;
    int altura, anchura, medio;

public:
    Mapa(int filas, int columnas);

    ~Mapa();

    bool actualizarMapa(Pieza* piezaNueva, Pieza* piezaAntigua, bool abajo);

    void printMapa(int puntuacion);

    int hayLineaCompleta();

    int limpiarLinea();

    bool hayColision(Pieza* piezaNueva);

    int getMedio();
};
