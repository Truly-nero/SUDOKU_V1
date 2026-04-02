#pragma once

enum tEstado { ORIGINAL, OCUPADA, VACIA};

class Celda {
private:
	tEstado estado;
	int valor;

public:
	Celda();
	Celda(int v, tEstado est);
	//S metodos de consulta
	bool es_vacia();
	bool es_original();
	bool es_ocupada();
	int dame_valor() const;
	// metodos modificadores
	void set_valor(int v);
	void set_ocupada();
	void set_original();
	void set_vacia();
};

