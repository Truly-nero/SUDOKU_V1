#include <iostream>
#include "ReglasSudoku.h"

using namespace std;

void mostrar_menu();

int main() {

	ReglasSudoku r = ReglasSudoku::ReglasSudoku();

	ifstream archivo;
	string nombre;

	cout << "Introduce el nombre del archivo: ";
	cin >> nombre;
	cout << endl;

	archivo.open(nombre);

	if (!archivo.is_open()) {
		cout << "No se ha encontrado el archivo." << endl;
	}
	else {
		int op = 0;
		r.carga_sudoku(archivo);
		archivo.close();
		//mostrar_sudoku(r);

		mostrar_menu();
		cout << "Elige una opcion: ";
		cin >> op;

		while (op != 6 && !r.terminado()) {
			cout << endl;
			int f = 0, c = 0, v = 0;
			switch (op) {
			case 1:
				cout << "Fila y columna entre 1..." << MAX_DIM << ": ";
				cin >> f >> c;
				cout << endl << "Valor: ";
				cin >> v;
				cout << endl;
				if (!r.pon_valor(f, c, v)) {
					cout << "Error: No se puede poner ese valor." << endl;
				}
				break;
			case 2:
				cout << "Fila y columna entre 1..." << MAX_DIM << ": ";
				cin >> f >> c;
				cout << endl;
				if (!r.quita_valor(f,c)) {
					cout << "Error: No se puede quitar ese valor." << endl;
				}
				break;
			case 3:
				r.reset();
				break;
			case 4:
				cout << "Fila y columna entre 1..." << MAX_DIM << ": ";
				cin >> f >> c;
				cout << endl;
				if (!r.dame_celda(f, c).es_vacia()) {
					cout << "Error: la celda no es vacia." << endl;
				}
				else {
					cout << "Los valores posibles para la celda son: {";
					for (int i = 0; i < MAX_DIM; i++) {
						if (r.es_valor_posible(f, c, i)) {
							cout << " " << i << " ";
						}
					}
					cout << "}" << endl;
				}
				break;
			case 5:
				r.autocompletar();
				break;
			}

			if (r.bloqueo()) {
				cout << "Sudoku bloqueado.....Las casillas bloqueadas son: ";
				for (int i = 0; i < r.dame_num_celdas_bloqueadas(); i++) {
					r.dame_celda_bloqueada(i, f, c);
					cout << "(" << f << "," << c << ")";
				}
				cout << endl << "Prueba a quitar valores o hacer reset." << endl;
			}

			//mostrar_sudoku()
			mostrar_menu();
			cout << "Elige una opcion: ";
			cin >> op;
		}

		if (r.terminado()) {
			cout << "¡Suoku completado!" << endl;
		}

	}

	return 0;
}

void mostrar_menu() {
	cout << "1.- poner numero" << endl;
	cout << "2.- quitar numero" << endl;
	cout << "3.- reset" << endl;
	cout << "4.- posibles valores de una celda vacia" << endl;
	cout << "5.- autocompletar celdas con valor unico" << endl;
	cout << "6.- salir";
}