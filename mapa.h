#include "pieza.h"

class Mapa {
    char** mapa;
    int altura, anchura;

public:
    Mapa(int filas, int columnas);

    ~Mapa();

    void actualizarMapa(Pieza* piezaNueva, Pieza* piezaAntigua);

    void printMapa();

    int hayLineaCompleta();

    void limpiarLinea();
};
