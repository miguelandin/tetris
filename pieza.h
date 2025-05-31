class Pieza {
    int** bloques;

public:
    Pieza(int* valores);
    ~Pieza();
    void girar();
    void bajar();
};
