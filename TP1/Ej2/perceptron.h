#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <cstdlib>

#include "funciones.h"


using namespace std;

void generarPesos(int cantidad, vector<double> &w);
void entrenamiento(vector<double>&w, vector<double>x, double yd, double umbral);
void entrenador(vector<double> &w, mdouble entradas, vector<int>salidas, double umbral);
void prueba(vector<double> w, mdouble entradas, vector<int> salidas, vector<double> &error, double &correcto);
void extraer_matriz(mdouble m, int desde, int hasta, mdouble &submatriz);
void extraer_vector(vector<int> m, int desde, int hasta, vector<int> &subvector);
void particionar_matriz(mdouble m, int porcentaje, mdouble &parti1, mdouble &parti2);
void particionar_vector(vector<int> m, int porcentaje, vector<int> &parti1, vector<int> &parti2);
void particionador_pruebas(mdouble parti1, mdouble parti2, vector<int> salidas_parti1, vector<int> salidas_parti2, double umbral, double &prom);
void cantidad_particiones(int cant_parti, mdouble &entradas, vector<int> &salidas, int porcentaje, double umbral, vector<double> &e);

#endif
