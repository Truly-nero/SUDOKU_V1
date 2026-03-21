#include "ReglasSudoku.h"

using namespace std;

ReglasSudoku::ReglasSudoku() {
	cont = 0;
	num_bloq = 0;
}

/* consultoras */
int ReglasSudoku::dame_dimension() {
	return tab.dame_dim();
}

Celda ReglasSudoku::dame_celda(const int f, const int c) {
	return tab.dame_celda(f, c);
}

bool ReglasSudoku::terminado() {
	
}

bool ReglasSudoku::bloqueo() {
	return num_bloq != 0;
}
int ReglasSudoku::dame_num_celdas_bloqueadas() {
	return num_bloq;
}

void ReglasSudoku::dame_celda_bloqueada(const int p, int& f, int& c) {
	f = bloqueadas[p].f;
	c = bloqueadas[p].c;
}
bool ReglasSudoku::es_valor_posible(const int f, const int c, const int v) {
	bool correcto = true;

	if (!posicion_valida(f, c) || !valor_valido(v)) {
		correcto = false;
	}

	//falta la lógica de comprobar los valores de las demás casillas

	return correcto;
}

/* modificadoras */
bool ReglasSudoku::pon_valor(const int f, const int c, const int &v) {
	Celda celda = tab.dame_celda(f, c);
	bool correcto = false;

	if (posicion_valida(f,c) && valor_valido(v) && celda.es_vacia() && es_valor_posible(f,c,v)) {
		correcto = true;

		celda.set_valor(v);
		celda.set_ocupada();
		tab.colocar_celda(f, c, celda);

		cont++;
		//actualizar bloqueadas

	}

	return correcto;
}

bool ReglasSudoku::quita_valor(const int f, const int c) {
	bool correcto = false;
	Celda celda = tab.dame_celda(f, c);

	if (posicion_valida(f, c) && !celda.es_vacia()) {
		celda.set_vacia();
		celda.set_valor(0);
		tab.colocar_celda(f, c, celda);

		cont--;
		//actualizar bloqueadas
	}

	return correcto;
}
void ReglasSudoku::reset();

void autocompletar();

/* inicializadora */
void carga_sudoku(std::ifstream& archivo);

bool ReglasSudoku::posicion_valida(const int f, const int c) {
	int dim = tab.dame_dim();
	return (f >= 0 && f < dim && c >= 0 && c < dim);
}

bool ReglasSudoku::valor_valido(const int v){
	return (v >= 1 && v <= tab.dame_dim());
}