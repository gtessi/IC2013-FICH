#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>



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
	
	double vent_size=0.3;
	int max_epocas=300, cant_neuronas=20;
	
	cout<<"Processor v1.0 - 09/11/2013"<<endl
		<<"Ventana: "<<vent_size<<endl
		<<"Epocas: "<<max_epocas<<endl
		<<"Neuronas: "<<cant_neuronas<<endl<<endl;
	
	
	//readFile(entradas,"archivo.csv",true);
	readFile(entradas,"archivo.csv",false);
	readFile(ydeseada,"archivo.csv",false);
	int cantEntradas = entradas[0].size(),cantDatos=entradas.size();
	
	int j=0,
		cant=3;
	vdouble ioAux;
	
	cout<<"Comienza entrenamiento con "<<cantEntradas*cant<<" entradas y "
		<<cantDatos<<" patrones."<<endl;
	
	//show(entradas);
	
	
	// ****************** vector de neuronas *****************
//	neuronas.push_back(21);
//	neuronas.push_back(30);
//	neuronas.push_back(25);
	neuronas.push_back(cant_neuronas);
	neuronas.push_back(cantEntradas*cant);
	
	// Creamos la red
	redd = Red(neuronas, cantEntradas*cant);
	
	for(;j<max_epocas;j++){
		for (int i=0;i<cantDatos-cant;i++){
			
			// **********   PROPAGACION
			concatenar(entradas,i,cant,ioAux);
			redd.propagacion(ioAux);
			
			// **********   RETROPROPAGACION
			concatenar(ydeseada,i,cant,ioAux);
			redd.retropopagacion(ioAux);
			
			//cout<<"Epoca: "<<j<<" - Patron: "<<i<<endl;
		}
		cout<<"Epoca: "<<j<<endl;
	}
	
	// ************************************************************************
	
	cout<<endl<<"***************************************************"<<endl;
	
	cout<<"Epocas completadas: "<<j<<endl;
	cout<<"Termino el entrenamiento."<<endl<<endl;
	cout<<"Comenzado composicion..."<<endl;
	
	//int cantInstante=200;
	int cantInstante=entradas.size();
	
	vdouble instante,song,salidaI;
	mdouble cancion;
	
	// ******************************* INICIALIZAMOS LA PRIMERA ENTRADA
	instante.resize(cantEntradas*cant);

	//insertIn(instante,entradas[0],cant);
	
	pushPila(instante,entradas[0]);
	pushPila(instante,entradas[1]);
	pushPila(instante,entradas[2]);
	
	salidaI.resize(cantEntradas*cant);
	
	for(int i=0;i<cantInstante;i++){
		
		// ******************** PROPAGACION Y SALIDA
		redd.propagacion(instante);
		redd.salidas(salidaI);
		
		//show(salidaI);
		//cout<<endl;
		
		// ********************** SACAMOS LA ULTIMA PARTE DE LA SALIDA 
		// ********************** Y LA PONEMOS EN LA CANCION FINAL
		catVector(salidaI,song,cantEntradas,cant-1);
		cancion.push_back(song);
		
		// **********************  AGREGAMOS LA SALIDA PARA EL NUEVO
		// **********************  INSTANTE DE ENTRADA
		pushPila(instante,song);
		//insertIn(instante,song,cant);
	}
	
	
	// ************************* DESNORMALIZAMOS
	int cNotas=cancion[0].size(),
		cVentanas=cancion.size();
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
	
	cout<<"Composicion terminada."<<endl<<endl;
	
	// *********************** ARMAMOS LA MATRIZ MIDI CON Tini Tfin
	mdouble mMidi,cancionOrd;
	
	//filtrarOctavasTotal(cancion);
	//filtrarOctavasXventana(cancion);
	
	ordenar(cancion, vent_size, cancionOrd);
	makeMatrizMidi(cancionOrd,mMidi);
	
	// **************** Show
	//show(cancion);
	//cout<<endl<<"*******************************************"<<endl<<endl;
	//show(cancionOrd);
	//cout<<endl<<"*******************************************"<<endl<<endl;
	//show(mMidi);
	// ***********************
	
	saveV(cancionOrd,"cancion.csv");	
	//saveV(mMidi,"cancionMidi.csv");	
	
	//cout<<endl<<"****************** TERMINO TODOOO  *************"<<endl<<endl;
	cout<<endl<<"***************************************************"<<endl<<endl;
	//cin.get();
	return 0;
}

