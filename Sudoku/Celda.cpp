#include "Celda.h"

using namespace std;

Celda::Celda() {
	valor = 0;
	estado = VACIA;
}
Celda::Celda(int v, tEstado estado) {
	valor = v;
	estado = estado;
}
/* métodos de consulta */
bool Celda::es_vacia() {
	return estado == VACIA;
}
bool Celda::es_original() {
	return estado == ORIGINAL;
}
bool Celda::es_ocupada() {
	return estado == OCUPADA;
}
int Celda::dame_valor() {
	return valor;
}
/* métodos modificadores*/
void Celda::set_valor(int v) {
	valor = v;
}
void Celda::set_ocupada() {
	estado == OCUPADA;
}
void Celda::set_original() {
	estado == ORIGINAL;
}
void Celda::set_vacia() {
	estado == VACIA;
}