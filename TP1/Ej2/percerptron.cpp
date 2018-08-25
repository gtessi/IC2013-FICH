#include "perceptron.h"

using namespace std;

//Genera (cantidad) de pesos de forma aleatoria
void generarPesos(int cantidad, vector<double> &w){
	for(int i=0; i<cantidad; i++){
		w.push_back(valorAleatorio(-0.5,0.5));
	}
}

//Realiza el entrenamiento para la naurona
void entrenamiento(vector<double>&w, vector<double>x, double yd, double umbral){
	int n = x.size();
	double y = prodInterno(w,x);
	
	if(y<0)y=-1;
	else y=1;
	
	int error=yd-y;
	
	if(error!=0){
		for(int i=0;i<n;i++){
			w[i]=w[i]+umbral*(error)*x[i];
		}
	}
}

void entrenador(vector<double> &w, mdouble entradas, vector<int>salidas, double umbral){
	for (unsigned int i=0; i<entradas.size(); i++){
		entrenamiento(w,entradas[i], salidas[i],umbral);
	}
}


void prueba(vector<double> w, mdouble entradas, vector<int> salidas, vector<double> &error, double &correcto){
	//Realiza el producto punto entre los pesos y las entradas
	vector<double> y_vector;
	error.clear();
	correcto=0;
	int y=0;
	for(unsigned int i=0; i<entradas.size(); i++){
		//Aplico la funcion
		if(prodInterno(w,entradas[i])<0)
			y=-1;
		else
			y=1;
		
		y_vector.push_back(y);	
		
		//Calculo el error
		error.push_back(salidas[i]-y_vector[i]);
		
		//Cuenta si el valor es correcto o no
		if(y_vector[i]==salidas[i]){
			correcto++;
		}
	}
	
	correcto = correcto*100 / salidas.size();
}

//*** aca vienen los metodos para particionado ***

//Extrae una matriz, indicandole las posiciones "desde" y "hasta"
void extraer_matriz(mdouble m, int desde, int hasta, mdouble &submatriz){
	for(int i=desde; i<hasta; i++){
		submatriz.push_back(m[i]);
	}
}

//Extrae una vector, indicandole las posiciones "desde" y "hasta"
void extraer_vector(vector<int> m, int desde, int hasta, vector<int> &subvector){
	for(int i=desde; i<hasta; i++){
		subvector.push_back(m[i]);
	}
}

//Particiona una matriz, pasandole el porcentaje de la primera particion
void particionar_matriz(mdouble m, int porcentaje, mdouble &parti1, mdouble &parti2){
	int particion1, particion2;
	
	//Define como numero entero el porcentaje para particiones de entrenamiento y prueba
	particion1=(m.size()*porcentaje)/100;
	particion2=(m.size()*(100-porcentaje))/100;
	
	//Extrae los datos para entrenamiento y prueba segun los enteros para cada particion
	extraer_matriz(m,0,particion1,parti1);
	extraer_matriz(m,particion1,particion1+particion2,parti2);    
}

//Particiona un vector, pasandole el porcentaje de la primera particion
void particionar_vector(vector<int> m, int porcentaje, vector<int> &parti1, vector<int> &parti2){
	int particion1, particion2;
	
	//Define como numero entero el porcentaje para particiones de entrenamiento y prueba
	particion1=(m.size()*porcentaje)/100;
	particion2=(m.size()*(100-porcentaje))/100;
	
	//Extrae los datos para entrenamiento y prueba segun los enteros para cada particion
	extraer_vector(m,0,particion1,parti1);
	extraer_vector(m,particion1,particion1+particion2,parti2);  
}

//Dados dos conjuntos de entrada (entrenamiento y pruebas) y dos salidas (entrenamiento y pruebas), calcula el promedio prom de los errores cometidos
void particionador_pruebas(mdouble parti1, mdouble parti2, vector<int> salidas_parti1, vector<int> salidas_parti2, double umbral, double &correct){
	vector<double> w, e;
	correct=0;
	
	bool next=true;
	int epocas=10;
	double tasa_aciertos=95;
	
	//Vector de pesos
	generarPesos(parti1[0].size(),w);
	
	//aca van los criterios de corte por epocas y tasa de aciertos
	while(next){
		entrenador(w,parti1,salidas_parti1,umbral);
		prueba(w,parti1,salidas_parti1,e,correct);
		
		epocas-=1;
		
		if(epocas==0){
			next=false;
			//cout<<"Sale por epocas"<<endl;
		}
		
		if(correct>tasa_aciertos){
			next=false;
			//cout<<"Sale por aciertos"<<endl;
		}
	}
	
	prueba(w,parti2,salidas_parti2,e,correct);
}

//Genera cant_parti particiones, segun un porcentaje para entrenar (100-porcentaje=pruebas), y devuelve el promedio de errores de cada particion
void cantidad_particiones(int cant_parti, mdouble &entradas, vector<int> &salidas, int porcentaje, double umbral, vector<double> &e){
	mdouble mparti1, mparti2;
	vector<int> vparti1, vparti2;
	
	double prom=0;
	
	for(int i=0; i<cant_parti; i++){
		//Desordena los datos
		mezclar(entradas,salidas);
		
		particionar_matriz(entradas, porcentaje, mparti1, mparti2);
		particionar_vector(salidas, porcentaje, vparti1, vparti2);
		
		particionador_pruebas(mparti1, mparti2, vparti1, vparti2, umbral, prom);
		
		//guarda la tasa de aciertos (prom)
		e.push_back(prom);
		
		// clear
		mparti1.clear();
		mparti2.clear();
		vparti1.clear();
		vparti2.clear();
		prom=0;
	}
}
