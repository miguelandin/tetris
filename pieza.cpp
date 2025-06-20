#include "pieza.h"

Pieza::Pieza(const int* pieza, int medio)
{
    this->pieza = new int[LEN];

    for (int i = 0; i < LEN / 2; i++) {
        this->pieza[i * 2] = pieza[i * 2];
        this->pieza[i * 2 + 1] = pieza[i * 2 + 1] + medio;
    }
}

Pieza::~Pieza()
{
    delete[] pieza;
    pieza = nullptr;
}

int* Pieza::getCoordenadas()
{
    return pieza;
}

void Pieza::rotar()
{ // rotación en sentido horario
    int x, y, centroX, centroY;
    centroX = pieza[2];
    centroY = pieza[3];

    for (int i = 0; i < LEN / 2; i++) {
        x = pieza[i * 2] - centroX;
        y = pieza[i * 2 + 1] - centroY;

        // nuevos valores rotados
        pieza[i * 2] = centroX + y; // nueva x
        pieza[i * 2 + 1] = centroY - x; // nueva y
    }
}

void Pieza::moverIzquierda()
{
    for (int i = 0; i < LEN / 2; i++)
        pieza[i * 2 + 1] -= 1; // resta 1 a las x (hacia la izquierda)
}

void Pieza::moverDerecha()
{
    for (int i = 0; i < LEN / 2; i++)
        pieza[i * 2 + 1] += 1; // suma 1 a las x (hacia la derecha)
} // suma 1 a las y (hacia abajo)

void Pieza::bajar()
{
    for (int i = 0; i < LEN / 2; i++)
        pieza[i * 2] += 1; // suma 1 a las y (hacia abajo)
}

bool Pieza::mover(char imput)
{
    switch (imput) {
    case 'w':
        rotar();
        break;
    case 'a':
        moverIzquierda();
        break;
    case 's':
        bajar();
        return true; // si se mueve hacia abajo, devuelve true
        break;
    case 'd':
        moverDerecha();
        break;
    }

    return false;
}
