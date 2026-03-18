#include "Tablero.h"

using namespace std;

Tablero::Tablero() {
    for (int i = 0; i < MAX_DIM; i++) {
        for (int j = 0; j < MAX_DIM; j++) {
            matrizCeldas[i][j] = Celda();
        }
    }
}

Tablero::Tablero(const int d) {
    dim = d;

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matrizCeldas[i][j] = Celda();
        }
    }
}

int Tablero::dame_dim() {
    return dim;
}

Celda Tablero::dame_celda(const int f, const int c) {
    return matrizCeldas[f][c];
}

void Tablero::colocar_celda(const int f, const int c, const Celda& celda) {
    matrizCeldas[f][c] = celda;
}
