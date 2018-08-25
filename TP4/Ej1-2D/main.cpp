
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

// librerias calcular el tiempo que tarda
#include<ctime>

clock_t startC, finishC;


using namespace std;

#include "funcionesAux.h"
#include "individuo.h"
#include "poblacion.h"

poblacion poblado;

int main (int argc, char **argv) {
	
	srand(time(NULL));
	int cantPobla=100, cantGene=20;
	
	poblado = poblacion(cantPobla,cantGene);
	
	poblado.mostrarTodo();
	
	cin.get();
	
	startC = clock();
	for(int i=0;i<1000;i++){
		poblado.selectProgenitores(20);
		poblado.mezclarProgenitores();
		poblado.showBest();
		cin.get();
	}
	finishC = clock();
	cout << "Time (difftime): " << difftime(finishC, startC)/1000000.0<< endl;
	
	poblado.showBest();
	cin.get();
	return 0;
}
