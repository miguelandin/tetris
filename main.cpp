#include <cstdlib>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "mapa.h"

void clear()
{
    system("clear");
}

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

int main()
{
    Mapa mapa(14, 10);

    char c;
    std::cout << "Introduce caracteres (presiona 'q' para salir): " << std::endl;

    while (true) {
        c = getch(); // Llama a la función para leer un carácter
        if (c == 'q') { // Condición para salir
            break;
        }
        clear();
        mapa.printMapa();

    }

    return 0;
}
