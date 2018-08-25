#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include "funciones.h"

using namespace std;

void generarPesos(int cantidad, vector<double> &w);
void entrenamiento(vector<double> &w, vector<double> x, double yd, double umbral);
void entrenador(vector<double> &w, mdouble entradas, vector<int> salidas, double umbral);
void prueba(vector<double> w, mdouble entradas, vector<int> salidas, vector<double> &error, double &correcto);

#endif
