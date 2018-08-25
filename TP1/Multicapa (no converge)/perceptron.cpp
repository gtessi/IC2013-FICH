#include "perceptron.h"

using namespace std;

perceptron::perceptron(int cant_entradas, double tasa_aprendizaje, double momento) {
	mu=tasa_aprendizaje;
	nu=momento;
	y=0;
	delta=0;
	generarPesos(cant_entradas+1); //+1 por el bias de cada neurona, no incluirlo en el dato de entrada
}

void perceptron::generarPesos(int cantidad){
	for(int i=0; i<cantidad; i++){
		w.push_back(valorAleatorio(-0.6,0.6));
		w_ant.push_back(0.0);
	}
}

double perceptron::calcularSalida(vdouble x){
	double v=0;
	
	v=prodInterno(w,x);
//	for(unsigned int i=0; i<x.size(); i++)
//		v+=w[i]*x[i];
	
	y=sig(v);
	//y=2/(1+exp(-v))-1;
	
	return y;
}

double perceptron::devolverSalida(){
	return y;
}

void perceptron::guardarDelta(double d){
	delta=d;
}

double perceptron::devolverDelta(){
	return delta;
}

vdouble perceptron::devolverPesos(){
	return w;
}

void perceptron::guardarPesos(vdouble p){
	w=p;
}

vdouble perceptron::devolverPesosAnt(){
	return w_ant;
}

void perceptron::guardarPesosAnt(vdouble p){
	w_ant=p;
}

double perceptron::devolverMu(){
	return mu;
}

double perceptron::devolverNu(){
	return nu;
}

void perceptron::mostrar_pesos(){
	mostrar_vector(w);
}

void perceptron::mostrar_salida(){
	cout<<"Salida: "<<y<<endl<<endl;
}
