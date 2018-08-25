#include "perceptron.h"


using namespace std;

//Genera (cantidad) de pesos de forma aleatoria
void generarPesos(int cantidad, vector<double> &w){
	for(int i=0; i<cantidad; i++){
		w.push_back(valorAleatorio(-0.5,0.5));
	}
}

//Realiza el entrenamiento para la naurona
void entrenamiento(vector<double> &w, vector<double> x, double yd, double umbral){
	int n = x.size();
	double y = prodInterno(w,x);
	
	if(y<0)
		y=-1;
	else
		y=1;
	
	int error=yd-y;
	
	if(error!=0){
		for(int i=0;i<n;i++){
			w[i]=w[i]+umbral*(error)*x[i];
		}
	}
}

void entrenador(vector<double> &w, mdouble entradas, vector<int> salidas, double umbral){
	for (unsigned int i=0; i<entradas.size(); i++){
		entrenamiento(w,entradas[i], salidas[i],umbral);
	}
}


void prueba(vector<double> w, mdouble entradas, vector<int> salidas, vector<double> &error, double &correcto){
	//Realiza el producto punto entre los pesos y las entradas
	vector<double> y_vector;
	error.clear();
	correcto=0;
	int y=0;
	for(unsigned int i=0; i<entradas.size(); i++){
		//Aplico la funcion
		if(prodInterno(w,entradas[i])<0) y=-1;
		else y=1;
		y_vector.push_back(y);	
		
		//Calculo el error
		error.push_back(salidas[i]-y_vector[i]);
		
		//Cuenta si el valor es correcto o no
		if(y_vector[i]==salidas[i]){
			correcto++;
		}
	}	
	correcto = correcto*100 / salidas.size();
}
