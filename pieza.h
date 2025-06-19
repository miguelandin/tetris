class Pieza {
    int* pieza;

    const int LEN = 8;

public:
    Pieza(const int* pieza, int medio);

    ~Pieza();

    int* getCoordenadas();

    void rotar();

    void moverIzquierda();

    void moverDerecha();

    void bajar();

    bool mover(char imput);
};
