#include <cmath>

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
	
	int cant = ww.size();
	
	double min =-0.6,max=0.6;
	srand(time(NULL)+iteRand);
	iteRand++;
	//srand(time(NULL));
	for(int i=0; i<cantidad; i++){
		
		W.push_back(double(rand()*(max-min)/RAND_MAX + min));
		//W.push_back(((rand() % 100) -50)/100.0);
		//W.push_back(ww[i%cant]);
		//ww[i%cant]=ww[i%cant]+0.1;
	}
	
	
}

void generarZeros(int cantidad, vector<double> &W){
	W.clear();
	for(int i=0; i<cantidad; i++){
		W.push_back(0);
	}
}


