#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <fstream>

using namespace std;

typedef vector<double> vdouble;
typedef vector<int> vint;

typedef vector<vdouble> mdouble;


typedef mdouble::iterator itm; //iterator para recorrer la matriz
typedef vint::iterator iti; //iterator para recorrer vectores <int>
typedef vdouble::iterator itd; //iterator para recorrer vectores <double>


void explode(string line, mdouble &X, vector<int> &Y, bool insX0);
void readFile(mdouble &X, vector<int> &Y, string file, bool insX0);
void saveFile(mdouble &X, vector<int> &y, string file);
double valorAleatorio(double min, double max);
double prodInterno(vector<double> &w, vector <double> &x);
vector<double> VectorDeDesvio(vector<double> desvio, double disp, bool menosuno);
void getRandMatrix(mdouble &entradas, vector<int> &salidas, int val, double disp);
void mostrar_vector(vector<double> x);
void mostrar_vector(vector<int> x);
void mostrar_matriz(mdouble x);
void mezclar(mdouble &entradas, vector<int> &salidas);
double promedio(vdouble vector);

#endif
