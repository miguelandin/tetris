class Pieza {
    int** bloques;

public:
    Pieza(int* valores, int medio);

    ~Pieza();

    void girar();

    void bajar();

    void izquierda();

    void derecha();

    int **getCoordenadas();
};
