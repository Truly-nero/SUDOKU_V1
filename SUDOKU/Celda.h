#pragma once
#include <iostream>

class Celda {
	typedef enum { ORIGINAL, OCUPADA, VACIA } tEstado;
private:
	tEstado estado;
	int valor;
public:
	Celda();
	Celda(int v, tEstado est);
	/* métodos de consulta */
	bool es_vacia();
	bool es_original();
	bool es_ocupada();
	int dame_valor();
	/* métodos modificadores*/
	void set_valor(int v);
	void set_ocupada();
	void set_original();
	void set_vacia();
};

