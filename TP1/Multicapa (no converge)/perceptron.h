#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>

#include "funciones.h"

using namespace std;

typedef vector<double> vdouble;
typedef vector<int> vint;

typedef vector<vdouble> mdouble;

class perceptron {
private:
	//variables
	vdouble w; //vector de pesos
	vdouble w_ant; //vector de pesos de la iteracion anterior (momento)
	
	double mu; //tasa de aprendizaje
	double nu; //termino de momento
	
	double y; //salida
	double delta; //delta
	
	//metodos
	void generarPesos(int cantidad);
protected:
	
public:
	//constructores
	perceptron(int cant_entradas, double tasa_aprendizaje, double momento);
	
	//metodos
	double calcularSalida(vdouble x);
	
	double devolverSalida();
	
	void guardarDelta(double d);
	double devolverDelta();
	
	vdouble devolverPesos();
	void guardarPesos(vdouble p);
	
	vdouble devolverPesosAnt();
	void guardarPesosAnt(vdouble p);
	
	double devolverMu();
	double devolverNu();
	
	void mostrar_pesos();
	
	void mostrar_salida();
};

#endif

