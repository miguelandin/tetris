class Mapa {
    char** display;
    int altura;
    int anchura;

public:
    Mapa(int alto, int ancho);

    ~Mapa();

    void printMapa();
};
