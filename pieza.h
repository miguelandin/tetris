class Pieza {
    int* pieza;

    const int LEN = 8;

public:
    Pieza(const int* pieza);

    ~Pieza();

    int* getCoordenadas();

    void rotar();

    void moverIzquierda();

    void moverDerecha();

    void bajar();

    void mover(char imput);
};
