#ifndef RED_H
#define RED_H

#include <vector>

#include "perceptron.h"

typedef vector<perceptron> capa;

using namespace std;


class red {
private:
	//variables
	capa c; //conjunto de perceptrones
	vector<capa> r; //conjunto de capas
	
	vector<vdouble> entradas; //vector con las entradas para cada capa
	vdouble errores; //vector con los errores de la capa de salida
	
protected:
	
public:
	//constructores
	red(vector<int> estructura, double tasa_aprendizaje, double momento);
	
	//metodos
	void propagarAdelante(vdouble x);
	
	void propagarAtras(int y_deseada);
	
	void actualizarPesos();
	
	void retropropagacion(vdouble x, int y_deseada);
	
	double prueba(vdouble x);
	
};

#endif

