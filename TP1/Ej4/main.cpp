#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>



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

mdouble original_ent, entrenamiento_temp, entrenamiento_test, ydeseada, salidas_temp, salidas_test;
vdouble original_sal;

int k, cantEpocas;

Red redd;
bool equisOR;


int main (int argc, char **argv) {
	
	// Leemos la base de datos
	readFile(original_ent,original_sal,"iris.csv",true);
	
	// Mezcla los datos
	mezclar(original_ent,original_sal);
	
	// Asignamos la cantidad de neuronas para cada capa
	neuronas.push_back(5);
	//neuronas.push_back(4);
	neuronas.push_back(3);
	//neuronas.push_back(3);
	
	int cantEntradas = original_ent[0].size(),cantDatos=original_ent.size();
	
	vdouble aux;
	aux.push_back(-1);
	aux.push_back(-1);
	aux.push_back(-1);
	
	
	//codificacion de las salidas
	for(int i=0;i<cantDatos;i++){
		if(original_sal[i]==0.0){
			ydeseada.push_back(aux);
			ydeseada[i][0]=1;
		}
		if(original_sal[i]==1.0){
			ydeseada.push_back(aux);
			ydeseada[i][1]=1;
		}
		if(original_sal[i]==2.0){
			ydeseada.push_back(aux);
			ydeseada[i][2]=1;
		}
	}
	
	// Creamos la red
	redd = Red(neuronas, cantEntradas);
	
	
//	cout<<"Pesos iniciales"<<endl;
//	redd.showPesos();	
//	cout<<endl;
	
	// Define las epocas
	cantEpocas=100;
	
	// *** aca viene la cosa
	vdouble porcentajes;
	
	cout<<"Ingrese el k deseado: ";
	cin>>k;
	
	cout<<endl<<" *********************** "<<endl<<"Cantidad de patrones: "<<original_ent.size()<<endl;
	cout<<"k elegido: "<<k<<endl;
	
	// Calcula el k optimo para no dejar conjuntos desiguales
	while (original_ent.size() % k != 0)
		k--;
	
	cout<<"k optimo: "<<k<<endl;
	cout<<" *********************** "<<endl;
	
	system("pause");
	
	int limite=original_ent.size()/k;
	
	for (int i=0; i<limite; i++){
		double porcent=0;
		
		// Copia las matrices
		entrenamiento_temp=original_ent;
		salidas_temp=ydeseada;
		
		// Particiona segun k
		particionador(entrenamiento_temp,salidas_temp,k,i,entrenamiento_test,salidas_test);
		
		// Cantidad de patrones
		int cantPatrones=entrenamiento_temp.size();
		
		// Entrena
		bool bandera_corte=true;
		
		for (int j=0; j<cantEpocas; j++){
			for (int l=0; l<cantPatrones; l++){
				redd.propagacion(entrenamiento_temp[l]);
				redd.retropopagacion(salidas_temp[l],entrenamiento_temp[l]);
			}
			
			double aciertos=redd.pruebaIris(salidas_temp,entrenamiento_temp);
			
			//cout<<"Acertados: "<<aciertos<<"% - epoca: "<<j+1<<endl;
			
			if(aciertos>93){
//				cout<<"Epocas completadas:  "<<j+1<<endl;
//				cout<<endl;
				j=100000000;
				bandera_corte=false;
				cout<<endl<<endl<<" ***Corte: Por Tolerancia*** "<<endl<<endl;
//				system("pause");
			}
		}
		
		if(bandera_corte){
			cout<<endl<<endl<<" ***Corte: Por Epocas*** "<<endl<<endl;
//			system("pause");
		}
		
		// Muestra los pesos
		//cout<<"Pesos Finales"<<endl;
		//redd.showPesos();
		
		//cout<<"Pesos finales guardados"<<endl;
		redd.savePeso();
		
		// Prueba
		for (int l=0; l<k; l++){
			porcent=redd.pruebaIris(salidas_test,entrenamiento_test);
			
			// Agrega el porcentaje
			porcentajes.push_back(porcent);
		}
		
		// Muestra los porcentajes de aciertos de cada particion
		cout<<"Particion: "<<i+1<<" - Porcentaje: "<<porcentajes.back()<<endl;
	}
	
	// Calcula el promedio de los porcentajes de aciertos
	double prom=promedio(porcentajes);
	
	// Calcula el desvio estandar
	double desv=desvioEstandar(porcentajes,prom);
	
	// Muestra el promedio de los porcentajes de aciertos
	cout<<"------------------------"<<endl<<endl<<"Media: "<<prom<<endl<<"Desvio estandar: "<<desv<<endl;
	
//	glutInit (&argc, argv);
//	initialize();
//	glutMainLoop();
	
	return 0;
}
