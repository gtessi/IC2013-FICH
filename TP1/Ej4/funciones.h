#include <cmath>
#include <ctime>
#include <algorithm>

using namespace std;

extern vdouble ww;
extern int iteRand;

// producto entre Matriz Vector
void productoMV(mdouble matriz, vdouble vector, vdouble &v){
	
	// verifica si la cantidad de columnas es la
	// misma que la longitud del vector
	if(matriz[0].size()!=vector.size()){
		cout<<"Error productoMV: "<<matriz[0].size()<<"  "<<vector.size()<<endl;
		return ;
	}
	
	// Limpiamos el vector de retorno
	v.clear();
	
	// Cantidad de renglones 
	int smatriz = matriz.size(),
		// cantidad de columnas
		svector = vector.size();
	// variable auxiliar
	double aux=0;
	
	for(int i=0;i<smatriz;i++){
		for(int j=0;j<svector;j++){
			aux=matriz[i][j] * vector[j]+aux;
		}
		
		// Funcion sigmoida
		aux= 2 / (1+exp(-aux)) - 1;
		// agregamos el nuevo valor al vector de salida
		v.push_back(aux);
		aux=0;
	}
	
}

// Producto entre Vector Matriz
void productoVM(vdouble vector, mdouble matriz, vdouble &v){
	
	
	if(vector.size()!=matriz.size()){
		cout<<"Error productoVM: "<<vector.size()<<"  "<<matriz.size()<<endl;
		return;
	}
	
	v.clear();
	int svector = matriz[0].size(),smatriz=matriz.size();
	double aux=0;
	
	
	for(int i=0; i<svector;i++){
		for(int j=0;j<smatriz;j++){
			aux=(vector[j]*matriz[j][i])+aux;
		}
		v.push_back(aux);
		aux=0;
	}
}

// Muestra un Vector
void show(vector<double> x){
	for(int i=0;i<x.size();i++)
		cout<<x[i]<<"  ";
	cout<<endl;
}


// Muestra una matriz
void show(vector< vector< double> > x){
	
	for(int j=0;j<x.size();j++){
		for(int i=0;i<x[0].size();i++)
			cout<<x[j][i]<<"  ";
		cout<<endl;
	}
}


// Genera los pesos aleatoriamente
void generarPesos(int cantidad, vector<double> &W){
	W.clear();
	
	double min =-0.6,max=0.6;
	srand(time(NULL)+iteRand);
	iteRand++;
	for(int i=0; i<cantidad; i++){
		
		W.push_back(double(rand()*(max-min)/RAND_MAX + min));
	}
	
	
}

void maxElement(vdouble v, int &pos){
	double aux=0;
	int vSize = v.size();
	pos=-1;
	
	for(int i=0;i<vSize;i++){
		if(v[i]>aux){
			aux=v[i];
			pos=i;
		}
	}
}

void generarZeros(int cantidad, vector<double> &W){
	W.clear();
	for(int i=0; i<cantidad; i++){
		W.push_back(0);
	}
}

//Intercambia las posiciones de las entradas y salidas
void mezclar(mdouble &entradas, vector<double> &salidas){
	vector<int> posiciones;
	//Genero un vector de posiciones
	for (unsigned int i=0; i<entradas.size(); i++){
		posiciones.push_back(i);
	}
	//Intercalo las posiciones
	random_shuffle(posiciones.begin(),posiciones.end());
	
	for(unsigned int i=0; i<posiciones.size(); i++){
		entradas[posiciones[i]]=entradas[i];
		salidas[posiciones[i]]=salidas[i];
	}	
}

//Promedio de un vector
double promedio(vdouble vector){
	int n=vector.size();
	double prom=0;
	
	for (int i=0; i<n; i++){
		prom+=vector[i];
	}
	
	prom/=n;
	
	return prom;
}

//Desvio estandar
double desvioEstandar(vdouble vector, double media){
	double suma=0;
	int cant=vector.size();
	
	for (int i=0; i<cant; i++)
		suma+=(vector[i]-media)*(vector[i]-media);
	
	suma/=cant;
	
	suma=sqrt(suma);
	
	return suma;
}

//Particionador leave-k-out (el de la locura)
void particionador(mdouble &entradas, mdouble &salidas, int k, int iteracion, mdouble &inPruebas, mdouble &outPruebas){
	inPruebas.clear();
	outPruebas.clear();
	
	int ssize = salidas.size(); // tamanoParti = ssize / cantParti;
	
	//busca el k optimo para tener particiones que tomen todos los datos
//	while (ssize % k != 0)
//		k--;
	
	int tamanoParti=k;
	
	vector< vector <double> >::iterator e = entradas.begin() + tamanoParti*iteracion, s = salidas.begin() + tamanoParti*iteracion;
	
	
	for (int i=0;i<tamanoParti;i++){
		inPruebas.push_back(*e);
		outPruebas.push_back(*s);
		entradas.erase(e);
		salidas.erase(s);
	}
}


