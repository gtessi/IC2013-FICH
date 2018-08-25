#include "funciones.h"

using namespace std;

typedef vector<double> vdouble;
typedef vector<int> vint;

typedef vector<vdouble> mdouble;


typedef mdouble::iterator itm; //iterator para recorrer la matriz
typedef vint::iterator iti; //iterator para recorrer vectores <int>
typedef vdouble::iterator itd; //iterator para recorrer vectores <double>

/**
Dado un string, separa su contenido, separado por comas,
en valores numericos y los agrega a los vectores pasados por referencia
*/
void explode(string line, mdouble &X, vector<int> &Y, bool insX0){
	vector<double>Aux;
	//Segun la bandera insX0, inserta como primer elemento
	//el valor del X0 (-1) o no (no se necesita cuando particionamos)
	if(insX0)
		Aux.push_back(-1); //Valor que proporciona movilidad a la recta (abcisa)
	
	char Buffer[25]; //Maximo 25 cifras
	//for(int l=0;l<25;l++) Buffer[l] = '\0';
	int i = 0;
	//Lee el string hasta el final
	for (int k=0; line[k] != '\0'; k++){
		//Guarda los primero 'k' caracteres del
		//string hasta la coma en el Buffer
		if (line[k] != ','){
			Buffer[i] = line[k];
			i++;
		}else{
			//Sino, agrega una finalizacion al Buffer
			//y mete la cadena convertida en el vector auxiliar
			Buffer[i] = '\0';
			Aux.push_back(atof(Buffer));
			//Vacio el Buffer y posiciono el cursor en en inicio
			for(int l=0;l<25;l++) Buffer[l] = '\0';
			i = 0;
		}
	}
	Y.push_back(atoi(Buffer)); //El ultimo que lei es la salida	
	X.push_back(Aux); //Agrego las nuevas entradas como filas de la matriz
}


/**
Lee de un archivo valores de varias entradas y una salida separados por comas
*/
void readFile(mdouble &X, vector<int> &Y, string file, bool insX0){
	ifstream archi;
	archi.open(file.c_str());
	
	if(archi.is_open()){
		while(!archi.eof()){
			string str_line;
			getline(archi,str_line);
			
			if(!archi.eof())
				//Manda el string al parser para separar los datos
				//por comas en los vectores X y Y
				explode(str_line, X, Y, insX0);
		}
		
		archi.close();
	}
}


/**
Guarda en un archivo, datos separados por comas
*/
void saveFile(mdouble &X, vector<int> &y, string file){
	ofstream archi(file.c_str(), ios::trunc);
	
	unsigned int nRow=X.size(); //Numero de filas
	vector<double>::iterator itx;
	vector<int>::iterator ity=y.begin();
	
	if(archi.is_open()){	
		for (unsigned int i=0; i<nRow; i++){ //Habria que mejorar como lee el tamanio, por ahora funca
			//Graba los 'nCol' datos por filas
			for (itx=X[i].begin(); itx!=X[i].end(); itx++){
				archi<<*itx<<",";
			}
			//Graba el valor verdadero
			archi<<*(ity++)<<endl;
		}
		archi.close();
	}
}

//Generador de numero aleatorio en un rango
double valorAleatorio(double min, double max){
	// calcula el valor aleatorio entre min y max
	double val=double(rand()*(max-min)/RAND_MAX + min);
	
	return val;
}

//Realiza el producto interno dando como resultado 1 o -1
double prodInterno(vector<double> &w, vector <double> &x){
	int n = x.size();
	double val=0;
	for(int i=0;i<n;i++){
		val+=(w[i]*x[i]);
	}
	
	return val;
}

//Dado un vector, a cada elemento le aplica un desvio disp
//La bandera menosuno, es para ponerle un -1 adelante de todos los datos
vector<double> VectorDeDesvio(vector<double> desvio, double disp, bool menosuno){
	vector<double>desvio_aux=desvio;	
	desvio.clear();
	vector<double>::iterator p=desvio_aux.begin();
	if(menosuno){		
		desvio.push_back(-1);
		p++;
		for(; p!=desvio_aux.end(); p++){			
			desvio.push_back(*p+valorAleatorio(-disp,disp));
		}		
	}else{
		for(; p!=desvio_aux.end(); p++){
			desvio.push_back(*p+valorAleatorio(-disp,disp));
		}
	}
	return desvio;
	
}


//Para todas las entradas genera un desvio, la cantidad de veces (valor de val)
void getRandMatrix(mdouble &entradas, vector<int> &salidas, int val, double disp){
	mdouble entradas_aux=entradas;
	vector<int> salidas_aux=salidas;	
	entradas.clear();
	salidas.clear();	
	
	vector<double> aux;
	vector<double>::iterator p;
	int contador=0;
	while(contador<val){
		for (unsigned int i=0;i<salidas_aux.size();i++){
			for(vector<double>::iterator q=entradas_aux[i].begin(); q!=entradas_aux[i].end(); q++){
				aux.push_back(*q);
			}		
			entradas.push_back(VectorDeDesvio(aux,disp,true));
			salidas.push_back(salidas_aux[i]);
			aux.clear();
			contador++;
		}
	}
	
}


//Muestra el contenido de un vector
void mostrar_vector(vector<double> x){
	for(unsigned int i=0;i<x.size();i++)
		cout<<x[i]<<"  ";
	cout<<endl;
}
void mostrar_vector(vector<int> x){
	for(unsigned int i=0;i<x.size();i++)
		cout<<x[i]<<"  ";
	cout<<endl;
}
void mostrar_matriz(mdouble x){
	for(unsigned int i=0;i<x.size();i++){
		for(vector<double>::iterator p=x[i].begin(); p!=x[i].end(); p++){
			cout<<*p<<" ";
		}
		cout<<endl;
	}	
}

//Intercambia las posiciones de las entradas y salidas
void mezclar(mdouble &entradas, vector<int> &salidas){
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
