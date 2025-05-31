#include "pieza.h"

Pieza::Pieza(int* valores)
{
    bloques = new int*[4];
    for (int i = 0; i < 4; i++) {
        bloques[i] = new int[2];
        bloques[i][0] = valores[i * 2]; // X
        bloques[i][1] = valores[i * 2 + 1]; // Y
    }
}

Pieza::~Pieza()
{
    for (int i = 0; i < 4; i++)
        delete[] bloques[i];
    delete bloques;
}

void Pieza::girar(){
    // se estable el eje de rotación siempre en el segundo bloque
    int piboteX = bloques[1][0]; 
    int piboteY = bloques[1][1];

    for(int i = 0; i < 4; i++)
    {
        int x = bloques[i][0] - piboteX;
        int y = bloques[i][1] - piboteY;
        
        // rotar 90º
        bloques[i][0] = piboteX - y; // nueva x
        bloques[i][1] = piboteY + x; // nueva y
    }
}

void Pieza::bajar(){
    for(int i = 0; i < 4; i++)
        bloques[i][1] += 1; // se suma la altura en 1 (baja un bloque)
}
