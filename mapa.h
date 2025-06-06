
class Mapa {
    char** display;
    int altura;
    int anchura;

public:
    Mapa(int alto, int ancho);

    ~Mapa();

    void printMapa(char ** mapa);

    int getMedio();
    
    char** getMapa();

    void actualizarMapa(int **bloques);

    void actualizarTodoMapa(char** mapa);

    int getAltura();

    int getAncura();
};
