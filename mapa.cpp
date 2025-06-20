#include "mapa.h"
#include <iostream>
const int LEN = 8;

Mapa::Mapa(int alto, int ancho)
{
    altura = alto + 1; // se suma uno por el borde de abajo
    anchura = ancho + 2; // se suma dos porque los bordes consumen dos huecos
    medio = ancho / 2;
    mapa = new char*[altura]; // asigna memoria para las filas

    for (int i = 0; i < altura; i++) {
        mapa[i] = new char[anchura]; // asigna memoria para cada columna de una fila
        for (int j = 0; j < anchura; j++) {
            if (j == 0 || j == anchura - 1) // en caso de estar en los bordes
                mapa[i][j] = '|'; // delimita los lados
            else if (i == altura - 1)
                mapa[i][j] = '_'; // delimita el fondo
            else
                mapa[i][j] = 32; // char de espacio en blanco
        }
    }
}

Mapa::~Mapa()
{
    for (int i = 0; i < altura; i++)
        delete[] mapa[i];

    delete[] mapa;
    altura = 0;
    anchura = 0;
    mapa = nullptr;
}

bool Mapa::actualizarMapa(Pieza* piezaNueva, Pieza* piezaAntigua, bool abajo)
{ // borra la posicion antigua y pone la nueva posición en el mapa
    int* piezaA = piezaAntigua->getCoordenadas();
    int* piezaN = piezaNueva->getCoordenadas();

    if (!hayColision(piezaNueva)) {
        for (int i = 0; i < LEN / 2; i++)
            mapa[piezaA[i * 2]][piezaA[i * 2 + 1]] = 32; // borra la pieza antigua

        for (int i = 0; i < LEN / 2; i++)
            mapa[piezaN[i * 2]][piezaN[i * 2 + 1]] = '*'; // coloca la pieza nueva
    } else {
        delete piezaNueva; // elimina la pieza nueva ya que no es valida
        piezaNueva = new Pieza(piezaA, 0); // pasa a ser la pieza anterior // pasa a ser la pieza anterior
        if (abajo) {
            for (int i = 0; i < LEN / 2; i++)
                mapa[piezaA[i * 2]][piezaA[i * 2 + 1]] = '#'; // establece como colocada la pieza
            return true;
        }
    }

    return false;
}

void Mapa::printMapa(int puntuacion)
{
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < anchura; j++)
            std::cout << mapa[i][j];
        std::cout << std::endl;
    }
    std::cout << "SCORE: " << puntuacion;
}

int Mapa::hayLineaCompleta()
{
    bool completa;

    for (int i = 0; i < altura; i++) {
        completa = true;
        for (int j = 1; j < anchura - 1; j++)
            if (mapa[i][j] != '#') {
                completa = false;
                break; // sale del for porque ya sabemos que no es completa
            }
        if (completa)
            return i;
    }

    return -1;
}

int Mapa::limpiarLinea()
{
    int fila = hayLineaCompleta();
    int puntuacion = 0;

    while (fila != -1) {
        puntuacion += 1;
        puntuacion *= puntuacion;
        for (int i = fila; i > 0; i--) {
            for (int j = 0; j < anchura; j++)
                mapa[i][j] = mapa[i - 1][j];
        }

        for (int j = 1; j < anchura - 1; j++)
            mapa[0][j] = 32; // pasa a blanco la fila de la cima

        fila = hayLineaCompleta();
    }

    return puntuacion;
}

bool Mapa::hayColision(Pieza* piezaNueva)
{

    int* coordenadas = piezaNueva->getCoordenadas();

    for (int i = 0; i < LEN / 2; i++)
        if (mapa[coordenadas[i * 2]][coordenadas[i * 2 + 1]] == '|' || mapa[coordenadas[i * 2]][coordenadas[i * 2 + 1]] == '_' || mapa[coordenadas[i * 2]][coordenadas[i * 2 + 1]] == '#')
            return true;

    return false;
}

int Mapa::getMedio()
{
    return medio;
}
