#pragma once
#include "Celda.h"
const int MAX_DIM = 9;

class Tablero {
private:
	int dim;
	Celda matrizCeldas[MAX_DIM][MAX_DIM];

public:
	Tablero();
	Tablero(const int d);

	int dame_dim();
	Celda dame_celda(const int f, const int c);

	void colocar_celda(const int f, const int c, const Celda& celda);
};