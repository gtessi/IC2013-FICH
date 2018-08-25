#include <cmath>
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

void generarZeros(int cantidad, vector<double> &W){
	W.clear();
	for(int i=0; i<cantidad; i++){
		W.push_back(0);
	}
}



//Intercambia las entradas y salidas
void mezclar(mdouble &entradas, vector<int>&salidas){
	vector<int> posiciones;
	//Genero un vector de posiciones
	for (int i=0; i<entradas.size(); i++){
		posiciones.push_back(i);
	}
	//Intercalo las posiciones
	random_shuffle(posiciones.begin(),posiciones.end());
	
	for(int i=0; i<posiciones.size(); i++){
		entradas[posiciones[i]]=entradas[i];
		salidas[posiciones[i]]=salidas[i];
	}	
}


//Extrae una matriz, indicandole las posiciones "desde" "hasta"
void extraer_matriz(mdouble m, int desde, int hasta, mdouble &submatriz){
	for(int i=desde; i<hasta; i++){
		submatriz.push_back(m[i]);
	}
}
//Extrae una vector, indicandole las posiciones "desde" "hasta"
void extraer_vector(vector<double>m, int desde, int hasta, vector<double> &subvector){
	for(int i=desde; i<hasta; i++){
		subvector.push_back(m[i]);
	}
}

void particionar_matriz(mdouble m, int porcentaje, mdouble &parti1, mdouble &parti2){
	parti1.clear();
	parti2.clear();
	int particion1, particion2;
	particion1=(m.size()*porcentaje)/100;
	particion2=(m.size()*(100-porcentaje))/100;
	extraer_matriz(m,0,particion1,parti1);
	extraer_matriz(m,particion1,particion1+particion2,parti2);    
}
//Particiona un vector, pasandole el porcentaje de la primera particion
void particionar_vector(vector<double> m, int porcentaje, vector<double> &parti1, vector<double> &parti2){
	parti1.clear();
	parti2.clear();
	int particion1, particion2;
	particion1=(m.size()*porcentaje)/100;
	particion2=(m.size()*(100-porcentaje))/100;
	extraer_vector(m,0,particion1,parti1);
	extraer_vector(m,particion1,particion1+particion2,parti2);  
}

double promedio(vector<double> p){
	double suma=0.0;
	for(vector<double>::iterator o=p.begin(); o!=p.end(); o++){
		suma=suma+*o;
	}return suma/p.size();
}
double promedio(vector<int> p){
	double suma=0.0;
	for(vector<int>::iterator o=p.begin(); o!=p.end(); o++){
		suma=suma+*o;
	}return suma/p.size();
}

