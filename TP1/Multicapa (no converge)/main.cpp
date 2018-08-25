#include <iostream>

#include "red.h"

using namespace std;

vint estructura;

mdouble entradas;
vint salidas;

int op; //opcion
int epocas, max_epocas; //contadores de epocas
double tasa_aciertos, tolerancia; //tasa de aciertos

bool next=true; //bandera

int main (int argc, char **argv) {
	// genera semilla pseudoaleatoria
	srand(time(0));
	
	//define limites de entrenamiento
	max_epocas=500;
	tolerancia=93;
	
	//tasa de aprendizaje
	double tasa_aprendizaje=0.1;
	//momento
	double momento=0;
	//double momento=0.6; //=0 sin termino de momento
	
	
	//------------------- CONSULTAR -------------------
	//*** sin termino de momento, converge rapido pero a veces no
	//*** con termino de momento no converge nunca
	//*** con termino de momento, algunos deltas empiezan a dar NaN
	//-------------------------------------------------
	
	
	cout<<"*******************************************"<<endl;
	cout<<"              EJERCICIO 3"<<endl;
	cout<<"*******************************************"<<endl;
	cout<<endl<<endl;
	
	cout<<"Ingrese el ejercicio:"<<endl<<"Prueba XOR = 1"<<endl<<"Ejercicio 3 = 2"<<endl<<endl<<"Opcion: ";
	
	cin>>op;
	
	cout<<endl;
	
	switch(op){
	case 1:{
		cout<<"*** Prueba XOR ***"<<endl<<endl;
		
		//Carga el archivo base
		readFile(entradas,salidas,"entradasXOR.txt",true);
		
		// estructura de la red
		// la estructura es [entradas capa1 capa2 ... capaN (salida)]
		estructura.push_back(2); //entradas
		estructura.push_back(2); //capa 1 (oculta)
		//estructura.push_back(2);
		estructura.push_back(1); //capa 2 (salida)
		
		//inicializa la red
		red r(estructura,tasa_aprendizaje,momento);
		
		double y=0;
		double contador=0;
		
		//entrenamiento
		epocas=0;
		tasa_aciertos=0;
		while(next){
			//recorre los patrones
			for (unsigned int i=0; i<entradas.size(); i++)
				r.retropropagacion(entradas[i],salidas[i]);
			
			//los vuelve a recorrer para las pruebas
			for (unsigned int i=0; i<entradas.size(); i++){
				y=r.prueba(entradas[i]);
				
				if (y<0)
					y=-1;
				else
					y=1;
				
				if (y==salidas[i])
					contador++;
			}
			
			//incrementa el contador de epocas
			epocas++;
			
			//calcula la tasa de aciertos
			tasa_aciertos=contador*100/salidas.size();
			
			cout<<endl<<"*** Epoca: "<<epocas;
			cout<<endl<<"*** Tasa de aciertos parciales: "<<tasa_aciertos<<"%"<<endl;
			
			//criterios de corte
			//epocas
			if (epocas==max_epocas){
				next=false;
				cout<<endl<<"--- Sale por epocas ---"<<endl;
			}
			//tasa de aciertos
			if (tasa_aciertos>=tolerancia){
				next=false;
				cout<<endl<<"--- Sale por aciertos ---"<<endl;
			}
			
			//clear
			y=0;
			contador=0;
		}
		
		entradas.clear();
		salidas.clear();
		
		//pruebas
		//Carga el archivo base
		readFile(entradas,salidas,"pruebasXOR.txt",true);
		
		//recorre los patrones
		for (unsigned int i=0; i<entradas.size(); i++){
			y=r.prueba(entradas[i]);
			
			if (y<0)
				y=-1;
			else
				y=1;
			
////			mostrar_vector(entradas[i]);
////			cout<<" y= "<<y<<endl;
////			cout<<"yd= "<<salidas[i]<<endl<<endl;
			
			if (y==salidas[i])
				contador++;
		}
		
		//calcula la tasa de aciertos
		tasa_aciertos=contador*100/salidas.size();
		
		cout<<endl<<"*** Tasa de aciertos: "<<tasa_aciertos<<"%"<<endl;
		
		break;
	}
	case 2:{
		cout<<"*** Ejercicio 3 ***"<<endl<<endl;
		
		//Carga el archivo base
		//readFile(entradas,salidas,"concent.csv",true);
		readFile(entradas,salidas,"concent2.csv",true);
		
		// estructura de la red
		// la estructura es [entradas capa1 capa2 ... capaN (salida)]
		estructura.push_back(2); //entradas
		estructura.push_back(2); //capa 1 (oculta)
		//estructura.push_back(2);
		estructura.push_back(1); //capa 2 (salida)
		
		//inicializa la red
		red r(estructura,tasa_aprendizaje,momento);
		
		double y=0;
		double contador=0;
		
		//entrenamiento
		epocas=0;
		tasa_aciertos=0;
		while(next){
			//recorre los patrones
			for (unsigned int i=0; i<entradas.size(); i++)
				r.retropropagacion(entradas[i],salidas[i]);
			
			//los vuelve a recorrer para las pruebas
			for (unsigned int i=0; i<entradas.size(); i++){
				y=r.prueba(entradas[i]);
				
				//hay que comparar con -1 y 1
				if (y<0)
					y=-1;
				else
					y=1;
				
				if (y==salidas[i])
					contador++;
			}
			
			//incrementa el contador de epocas
			epocas++;
			
			//calcula la tasa de aciertos
			tasa_aciertos=contador*100/salidas.size();
			
			cout<<endl<<"*** Epoca: "<<epocas;
			cout<<endl<<"*** Tasa de aciertos parciales: "<<tasa_aciertos<<"%"<<endl;
			
			//criterios de corte
			//epocas
			if (epocas==max_epocas){
				next=false;
				cout<<endl<<"--- Sale por epocas ---"<<endl;
			}
			//tasa de aciertos
			if (tasa_aciertos>=tolerancia){
				next=false;
				cout<<endl<<"--- Sale por aciertos ---"<<endl;
			}
			
			//clear
			contador=0;
		}
		
		entradas.clear();
		salidas.clear();
		
		//pruebas
		//Carga el archivo base
		readFile(entradas,salidas,"concent2.csv",true);
		
		//recorre los patrones
		for (unsigned int i=0; i<entradas.size(); i++){
			y=r.prueba(entradas[i]);
			
			//hay que comparar con -1 y 1
			if (y<0)
				y=-1;
			else
				y=1;
			
			if (y==salidas[i])
				contador++;
		}
		
		//calcula la tasa de aciertos
		tasa_aciertos=contador*100/salidas.size();
		
		cout<<endl<<"*** Tasa de aciertos: "<<tasa_aciertos<<"%"<<endl;
		
		break;
	}
	}
	
	return 0;
}
