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
#include "Capa.h"
#include "Red.h"
#include "Readfile.h"

int main(int argc, char *argv[]) {
	ww.push_back(-0.1);ww.push_back(0.2);ww.push_back(0);
	// Definimos las variables
	vint neuronas;
	mdouble entradas;
	vdouble salidas,yd;
	
	// Leemos la base de datos
//	readFile(entradas,salidas,"concent2.csv",true);
	readFile(entradas,salidas,"entradasXOR.txt",false);
	
	// Asignamos la cantidad de neuronas paa cada capa
	neuronas.push_back(2);
	//neuronas.push_back(5);
	neuronas.push_back(1);
	int cantEntradas = entradas[0].size(),cantDatos=entradas.size();
	
	// Creamos la red
	Red redd = Red(neuronas, cantEntradas);
	
	cout<<"Comenzando entrenamiento con "<<cantEntradas<<" entradas y "
		<<cantDatos<<" cantidad de datos"<<endl;

//	cout<<"Pesos iniciales"<<endl;
//	redd.showPesos();	
//	cout<<endl;
	
	for(int j=0;j<25;j++){
		for (int i=0;i<cantDatos;i++){
			
//			redd.showPesos();
//			cout<<endl<<"--- Entradas ---"<<endl;
//			show(entradas[i]);
			
			redd.propagacion(entradas[i]);
			yd.push_back(salidas[i]);
			redd.retropopagacion(yd,entradas[i]);
			yd.clear();
			
//			cout<<"-----------------------------------------"<<endl;
//			cout<<"--- Salida ---  ";
//			redd.showSalida();
//			cout<<"--- Salida deseada --  ";
//			cout<<salidas[i]<<endl;
			
			
//			cout<<endl<<"--- Salidas ---"<<endl;
//			redd.showSalidas();
//			
//			cout<<"Salida deseada  "<<salidas[i]<<endl;
//			
//			cout<<endl<<"deltaientes"<<endl;
//			redd.showdeltaientes();
//			
//			cout<<"Pesos actualizados"<<endl;
//			redd.showPesos();
//			cout<<endl<<"----------------------------------------------"<<endl<<endl;
			
		}
		double aciertos=redd.prueba(salidas,entradas);
		cout<< "Acertados:  "<<aciertos<<"%"<<endl;
		if(aciertos>93){
			cout<<"Epocas completadas:  "<<j<<endl;
			cout<<"Pesos Finales"<<endl;
			redd.showPesos();	
			cout<<endl;
			return 0;}
		
	}

	return 0;
}


