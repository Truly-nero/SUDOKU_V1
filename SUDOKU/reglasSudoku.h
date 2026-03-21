#pragma once
#include "Tablero.h"
#include <fstream>

class ReglasSudoku {
private:
	Tablero tab;
	int cont;

	typedef struct {
		int f;
		int c;
	}tPosicion;

	tPosicion bloqueadas[MAX_DIM*MAX_DIM];
	int num_bloq;

	bool posicion_valida(const int f, const int c);
	bool valor_valido(const int v);
	void actualiza_bloqueadas();


public:
	ReglasSudoku();

	/* consultoras */
	int dame_dimension();
	Celda dame_celda(const int f, const int c);
	bool terminado();
	bool bloqueo();
	int dame_num_celdas_bloqueadas();
	void dame_celda_bloqueada(const int p, int& f, int& c);
	bool es_valor_posible(const int f, const int c, const int v);
	/* modificadoras */
	bool pon_valor(const int f, const int c, const int& v);
	bool quita_valor(const int f, const int c);
	void reset();
	void autocompletar();
	/* inicializadora */
	void carga_sudoku(std::ifstream& archivo);
};