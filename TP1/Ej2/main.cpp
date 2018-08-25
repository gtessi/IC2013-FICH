#include <iostream>
#include <vector>
#include <fstream>

#include "perceptron.h"

using namespace std;


//  VARIABLES
mdouble entradas;////Vector de entradas
vector<double> w; //Vector de pesos
vector<double> aciertos_particiones, ep10, ep50, ep70;
vector<int> salidas;//Vector de salidas

double nu=0.05; //=0.05 //Velocidad de Aprendizaje

int num_ejemplos; //Cantidad de ejemplos
double disp; //Dispersion de los datos

int num_particiones; //Cantidad de particiones a generar
double porcentaje=80; //Porcentaje para entrenamiento (100-porcentaje=pruebas) (80)

double acierto_promedio_total=0; //Promedio de los aciertos de entre todas las particiones

int op=1; //Parte a) (op=1) o b) (op=2) del ejercicio (Por defecto, toma op=1)

int main (int argc, char **argv) {
	// genera semilla pseudoaleatoria
	srand(time(0));
	
	
	cout<<"*******************************************"<<endl;
	cout<<"              EJERCICIO 2"<<endl;
	cout<<"*******************************************"<<endl;
	cout<<endl<<endl;
	
	cout<<"Ingrese el inciso del ejercicio:"<<endl<<"Inciso a) = 1"<<endl<<"Inciso b) = 2"<<endl<<endl<<"Opcion: ";
	
	cin>>op;
	
	cout<<endl;
	
	
	switch(op){
	case 1:
		cout<<"*** Inciso a) ***"<<endl<<endl;
		
		//Condiciones iniciales
		num_ejemplos=1000;
		disp=0.1; //Dispersion <10%
		num_particiones=5;
		
		//Carga el archivo base
		readFile(entradas,salidas,"datosA.txt",true);
		//Genera los casos de entrenamiento
		getRandMatrix(entradas,salidas,num_ejemplos,disp);
		//Guarda los datos en un archivo
		saveFile(entradas,salidas,"entradasA.txt");
		
		//Crea, entrena y prueba las particiones segun las condiciones dadas
		//Devuelve un vector con los promedios de errores cometidos en cada particion
		cantidad_particiones(num_particiones,entradas,salidas,porcentaje,nu,aciertos_particiones);
		
		//Calcula el promedio aciertos de entre todas las particiones
		acierto_promedio_total=promedio(aciertos_particiones);
		
		//Muestra los aciertos para cada particion
		cout<<"El promedio de aciertos de cada particion es: "<<endl<<endl;
		mostrar_vector(aciertos_particiones);
		cout<<endl<<"************"<<endl<<endl;
		
		//Muestra el promedio de aciertos en consola
		cout<<"El promedio de aciertos de entre todas las particiones es: "<<acierto_promedio_total<<endl<<endl<<"************"<<endl;
		
		break;
	case 2:
		cout<<"*** Inciso b) ***"<<endl<<endl;
		
		//Condiciones iniciales
		num_ejemplos=5000;
		num_particiones=5;
		
		//Carga el archivo base
		readFile(entradas,salidas,"datosB.txt",true);
		
		//Dispersion de 10%
		disp=0.1;
		//Genera los casos de entrenamiento
		getRandMatrix(entradas,salidas,num_ejemplos,disp);
		
		//Guarda los datos en un archivo
		saveFile(entradas,salidas,"entradasB10.txt");
		
		//Crea, entrena y prueba las particiones segun las condiciones dadas
		//Devuelve un vector con los promedios de errores cometidos en cada particion
		cantidad_particiones(num_particiones,entradas,salidas,porcentaje,nu,ep10);
		
		//Calcula el promedio de aciertos de entre todas las particiones
		acierto_promedio_total=promedio(ep10);
		
		//Muestra informacion por consola
		cout<<"Dispersion del "<<disp*100<<"%"<<endl<<"--------------------------"<<endl<<endl;
		
		//Muestra los aciertos para cada particion
		cout<<"El promedio de aciertos de cada particion es: "<<endl<<endl;
		
		for (unsigned int k=0; k<ep10.size(); k++)
			cout<<"Particion "<<k+1<<" -- Aciertos: "<<ep10[k]<<endl;
		
		cout<<endl<<"************"<<endl<<endl;
		
		//Muestra el promedio de aciertos en consola
		cout<<"El promedio de aciertos de entre todas las particiones es: "<<acierto_promedio_total<<endl<<endl<<"************"<<endl<<endl;
		
		system("pause");
		
		//----------------------------------------------------------------
		
		//Dispersion de 50%
		disp=0.5;
		//Genera los casos de entrenamiento
		getRandMatrix(entradas,salidas,num_ejemplos,disp);
		//Guarda los datos en un archivo
		saveFile(entradas,salidas,"entradasB50.txt");
		
		//Crea, entrena y prueba las particiones segun las condiciones dadas
		//Devuelve un vector con los promedios de errores cometidos en cada particion
		cantidad_particiones(num_particiones,entradas,salidas,porcentaje,nu,ep50);
		
		//Calcula el promedio de aciertos de entre todas las particiones
		acierto_promedio_total=promedio(ep50);
		
		//Muestra informacion por consola
		cout<<endl<<"Dispersion del "<<disp*100<<"%"<<endl<<"--------------------------"<<endl<<endl;
		
		//Muestra los aciertos para cada particion
		cout<<"El promedio de aciertos de cada particion es: "<<endl<<endl;
		
		for (unsigned int k=0; k<ep50.size(); k++)
			cout<<"Particion "<<k+1<<" -- Aciertos: "<<ep50[k]<<endl;
		
		cout<<endl<<"************"<<endl<<endl;
		
		//Muestra el promedio de aciertos en consola
		cout<<"El promedio de aciertos de entre todas las particiones es: "<<acierto_promedio_total<<endl<<endl<<"************"<<endl<<endl;
		
		system("pause");
		
		//----------------------------------------------------------------
		
		//Dispersion de 70%
		disp=0.7;
		//Genera los casos de entrenamiento
		getRandMatrix(entradas,salidas,num_ejemplos,disp);
		//Guarda los datos en un archivo
		saveFile(entradas,salidas,"entradasB70.txt");
		
		//Crea, entrena y prueba las particiones segun las condiciones dadas
		//Devuelve un vector con los promedios de errores cometidos en cada particion
		cantidad_particiones(num_particiones,entradas,salidas,porcentaje,nu,ep70);
		
		//Calcula el promedio de aciertos de entre todas las particiones
		acierto_promedio_total=promedio(ep70);
		
		//Muestra informacion por consola
		cout<<endl<<"Dispersion del "<<disp*100<<"%"<<endl<<"--------------------------"<<endl<<endl;
		
		//Muestra los aciertos para cada particion
		cout<<"El promedio de aciertos de cada particion es: "<<endl<<endl;
		
		for (unsigned int k=0; k<ep70.size(); k++)
			cout<<"Particion "<<k+1<<" -- Aciertos: "<<ep70[k]<<endl;
		
		cout<<endl<<"************"<<endl<<endl;
		
		//Muestra el promedio de aciertos en consola
		cout<<"El promedio de aciertos de entre todas las particiones es: "<<acierto_promedio_total<<endl<<endl<<"************"<<endl;
		
		break;
	}
	
	return 0;
}
