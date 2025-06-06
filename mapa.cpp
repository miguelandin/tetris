#include "mapa.h"
#include <iostream>

Mapa::Mapa(int alto, int ancho) {
  altura = alto + 1;   // se suma uno por el borde de abajo
  anchura = ancho + 2; // se suma dos porque los bordes consumen dos huecos
  display = new char *[altura]; // asigna memoria para las filas

  for (int i = 0; i < altura; i++) {
    display[i] =
        new char[anchura]; // asigna memoria para cada columna de una fila
    for (int j = 0; j < anchura; j++) {
      if (j == 0 || j == anchura - 1) // en caso de estar en los bordes
        display[i][j] = '|';          // delimita los lados
      else if (i == altura - 1)
        display[i][j] = '_'; // delimita el fondo
      else
        display[i][j] = 32; // char de espacio en blanco
    }
  }
}

Mapa::~Mapa() {
  for (int i = 0; i < altura; i++)
    delete[] display[i];
  delete display;
  altura = 0;
  anchura = 0;
}

void Mapa::printMapa(char **mapa) {
  for (int i = 0; i < altura; i++) {
    for (int j = 0; j < anchura; j++)
      std::cout << mapa[i][j];
    std::cout << std::endl;
  }
}

int Mapa::getMedio() { return anchura / 2; }

char **Mapa::getMapa() {
  char **mapa = new char *[altura];

  for (int i = 0; i < altura; i++) {
    mapa[i] = new char[anchura];
    for (int j = 0; j < anchura; j++)
      mapa[i][j] = display[i][j];
  }
  return mapa;
}

void Mapa::actualizarMapa(int **bloques) {
  int x, y;
  for (int i = 0; i < 4; i++) {
    x = bloques[i][0]; // obtiene la x del bloque i
    y = bloques[i][1]; // obtiene la y del bloque i
    display[x][y] = '#';
  }
}

void Mapa::actualizarTodoMapa(char **display) { this->display = display; }

int Mapa::getAltura() { return altura; }

int Mapa::getAncura() { return anchura; }
