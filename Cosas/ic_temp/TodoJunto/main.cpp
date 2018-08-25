#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>


using namespace std;

typedef vector<vector<double> > mdouble;
typedef vector<double> vdouble;
typedef mdouble::iterator itm;
typedef vector<int> vint;
typedef vector<double>::iterator itv;

vdouble ww;
int iteRand=0;


#include "funciones.h"
#include "Readfile.h"
#include "Capa.h"
#include "Red.h"


// Definimos las variables
vint neuronas;
mdouble entradas,ydeseada;
Red redd;

int main (int argc, char **argv) {
	
	neuronas.push_back(7);
//	neuronas.push_back(30);
//	neuronas.push_back(25);
//	neuronas.push_back(15);
	neuronas.push_back(7);
	
	readFile(entradas,"archivo.csv",true);
	readFile(ydeseada,"archivo.csv",false);
	int cantEntradas = entradas[0].size(),cantDatos=entradas.size();
	
	// Creamos la red
	redd = Red(neuronas, cantEntradas);
	
	cout<<"Comenzando entrenamiento con "<<cantEntradas<<" entradas y "
		<<cantDatos<<" cantidad de datos"<<endl;
	
	show(entradas);
	
	int j=0;
	for(;j<300;j++){
		for (int i=0;i<cantDatos;i++){
			redd.propagacion(entradas[i]);
			redd.retropopagacion(ydeseada[i]);
		}
		double error=redd.error(entradas);
		//cout<<"Error prom:  "<<error<<endl;
		if(error<0.3){
			break;
		}
	}
	
	
	// ************************************************************************
	
	cout<<endl<<"***************************************************"<<endl;
	
	cout<<"Epocas completadas:  "<<j+1<<endl;
	cout<<endl;
	
	cout<<"Termino el entrenamiento"<<endl;
	cout<<"Comenzamos composicion"<<endl;
	
	int cantInstante=213,
		pos=entradas.size();
	vdouble instanteI=entradas[0];
	mdouble cancion;
	for(int i=0;i<cantInstante;i++){
		//redd.propagacion(instanteI);
		redd.propagacion(entradas[i]);
		//show(entradas[i]);
		redd.salidas(instanteI);
		cancion.push_back(instanteI);
		instanteI.insert(instanteI.begin(),-1);
	}
	
	int cNotas=cancion[0].size(),
		cVentanas=cancion.size();
	
	// Desnormalizamos
	for(int l=0;l<cVentanas;l++){
		for(int p=0;p<cNotas;p++){
			if(cancion[l][p]<0)
				cancion[l][p]*=-1;
			if(cancion[l][p]<0.001)
				cancion[l][p]=0;
			else 
				cancion[l][p]=int(cancion[l][p]*100) ;
		}
	}
	
	cout<<endl<<"Composicion terminada"<<endl<<endl;
	
	mdouble mMidi,cancionOrd;
	ordenar(cancion, 0.1, cancionOrd);
	makeMatrizMidi(cancionOrd,mMidi);
	
	// **************** Show
	show(cancion);
	cout<<endl<<"*******************************************"<<endl<<endl;
	show(cancionOrd);
	cout<<endl<<"*******************************************"<<endl<<endl;
	show(mMidi);
	// ***********************
	
	saveV(cancionOrd,"cancion.csv");	
	saveV(mMidi,"cancionMidi.csv");	
	
	cin.get();
	return 0;
}

