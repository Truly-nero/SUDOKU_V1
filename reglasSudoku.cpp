#include "ReglasSudoku.h"
#include <cmath>

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
	return tab.dame_celda(f - 1, c - 1);
}

bool ReglasSudoku::terminado() {
	int dim = tab.dame_dim();
	return cont == dim * dim;
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
	int dim = tab.dame_dim();

	if (!posicion_valida(f, c) || !valor_valido(v) || !dame_celda(f, c).es_vacia()) {
		correcto = false;
	}
	else {
		// comprobar fila
		int j = 1;
		while (j <= dim && correcto) {
			if (j != c && !dame_celda(f, j).es_vacia() && dame_celda(f, j).dame_valor() == v) {
				correcto = false;
			}
			else {
				j++;
			}
		}

		// comprobar columna
		int i = 1;
		while (i <= dim && correcto) {
			if (i != f && !dame_celda(i, c).es_vacia() && dame_celda(i, c).dame_valor() == v) {
				correcto = false;
			}
			else {
				i++;
			}
		}

		// comprobar submatriz
		if (correcto) {
			int tam_sub = (int)sqrt(dim);

			int fila_ini = ((f - 1) / tam_sub) * tam_sub + 1;
			int col_ini = ((c - 1) / tam_sub) * tam_sub + 1;

			int fila = fila_ini;
			while (fila < fila_ini + tam_sub && correcto) {
				int col = col_ini;
				while (col < col_ini + tam_sub && correcto) {
					if (!(fila == f && col == c) &&
						!dame_celda(fila, col).es_vacia() &&
						dame_celda(fila, col).dame_valor() == v) {
						correcto = false;
					}
					else {
						col++;
					}
				}
				if (correcto) {
					fila++;
				}
			}
		}
	}

	return correcto;
}

/* modificadoras */
bool ReglasSudoku::pon_valor(const int f, const int c, const int& v) {
	bool correcto = false;
	Celda celda = dame_celda(f, c);

	if (posicion_valida(f, c) && valor_valido(v) && celda.es_vacia() && es_valor_posible(f, c, v)) {
		celda.set_valor(v);
		celda.set_ocupada();
		tab.colocar_celda(f - 1, c - 1, celda);

		cont++;
		actualiza_bloqueadas();
		correcto = true;
	}

	return correcto;
}

bool ReglasSudoku::quita_valor(const int f, const int c) {
	bool correcto = false;

	if (posicion_valida(f, c)) {
		Celda celda = dame_celda(f, c);

		if (!celda.es_vacia() && !celda.es_original()) {
			celda.set_vacia();
			tab.colocar_celda(f - 1, c - 1, celda);

			cont--;
			actualiza_bloqueadas();
			correcto = true;
		}
	}

	return correcto;
}

void ReglasSudoku::reset() {
	tab = original;

	cont = 0;
	int dim = tab.dame_dim();

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			if (!tab.dame_celda(i, j).es_vacia()) {
				cont++;
			}
		}
	}

	actualiza_bloqueadas();
}

void ReglasSudoku::autocompletar() {
	bool cambio;
	int dim = tab.dame_dim();

	do {
		cambio = false;

		for (int f = 1; f <= dim; f++) {
			for (int c = 1; c <= dim; c++) {
				if (dame_celda(f, c).es_vacia()) {
					int num_posibles = 0;
					int unico_valor = 0;

					for (int v = 1; v <= dim; v++) {
						if (es_valor_posible(f, c, v)) {
							num_posibles++;
							unico_valor = v;
						}
					}

					if (num_posibles == 1) {
						Celda celda = dame_celda(f, c);
						celda.set_valor(unico_valor);
						celda.set_ocupada();
						tab.colocar_celda(f - 1, c - 1, celda);

						cont++;
						cambio = true;
					}
				}
			}
		}
	} while (cambio);

	actualiza_bloqueadas();
}

/* inicializadora */
void ReglasSudoku::carga_sudoku(std::ifstream& archivo) {
	int dim;
	archivo >> dim;

	tab = Tablero(dim);
	original = Tablero(dim);
	cont = 0;
	num_bloq = 0;

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			int valor;
			archivo >> valor;

			Celda celda;

			if (valor == 0) {
				celda = Celda(0, VACIA);
			}
			else {
				celda = Celda(valor, ORIGINAL);
				cont++;
			}

			tab.colocar_celda(i, j, celda);
			original.colocar_celda(i, j, celda);
		}
	}

	actualiza_bloqueadas();
}

bool ReglasSudoku::posicion_valida(const int f, const int c) {
	int dim = tab.dame_dim();
	return (f >= 1 && f <= dim && c >= 1 && c <= dim);
}

bool ReglasSudoku::valor_valido(const int v) {
	return (v >= 1 && v <= tab.dame_dim());
}

void ReglasSudoku::actualiza_bloqueadas() {
	num_bloq = 0;
	int dim = tab.dame_dim();

	for (int f = 1; f <= dim; f++) {
		for (int c = 1; c <= dim; c++) {
			if (dame_celda(f, c).es_vacia()) {
				int num_posibles = 0;
				int v = 1;

				while (v <= dim && num_posibles == 0) {
					if (es_valor_posible(f, c, v)) {
						num_posibles++;
					}
					else {
						v++;
					}
				}

				if (num_posibles == 0) {
					bloqueadas[num_bloq].f = f;
					bloqueadas[num_bloq].c = c;
					num_bloq++;
				}
			}
		}
	}
}