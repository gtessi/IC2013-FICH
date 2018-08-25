#include <cmath>
#include <algorithm>

using namespace std;

/**
Dado un string, separa su contenido, separado por comas,
en valores numericos y los agrega a los vectores pasados por referencia
*/
void explode(string line, mdouble&X, bool insX0){
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
	Aux.push_back(atof(Buffer));
	X.push_back(Aux); //Agrego las nuevas entradas como filas de la matriz
	
	
	//Y.push_back(atoi(Buffer)); //El ultimo que lei es la salida
}


/**
Lee de un archivo valores de varias entradas separados por comas
*/
void readFile(mdouble &X, string file, bool insX0){
	ifstream archi;
	archi.open(file.c_str());
	
	if(archi.is_open()){
		while(!archi.eof()){
			string str_line;
			getline(archi,str_line);
			
			if(!archi.eof())
				//Manda el string al parser para separar los datos
				//por comas en los vectores X
				explode(str_line, X, insX0);
		}
		
		archi.close();
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
	double min =-.7,max=.7;
	for(int i=0; i<cantidad; i++){
		//srand(iteRand+i);
		W.push_back(double(rand()*(max-min)/RAND_MAX + min));
	}
}

//Funcion suma de vectores
vector<double> sumaV(vector<double> x1, vector<double> x2){
	int n1=x1.size();
	int n2=x2.size();
	vector<double> suma;
	
	if (n1!=n2)
		cout<<"ERROR - Vectores de diferente dimension"<<endl<<endl;
	else
		for(int i=0; i<n1; i++)
			suma.push_back(x1[i]+x2[i]);
	
	return suma;
}

//Funcion diferencia de vectores
vector<double> diferenciaV(vector<double> x1, vector<double> x2){
	int n1=x1.size();
	int n2=x2.size();
	vector<double> dif;
	
	if (n1!=n2)
		cout<<"ERROR - Vectores de diferente dimension"<<endl<<endl;
	else
		for(int i=0; i<n1; i++)
			dif.push_back(x1[i]-x2[i]);
	
	return dif;
}

//Funcion escalar-vector
vector<double> escalarV(double alfa, vector<double> x){
	int n=x.size();
	vector<double> vec;
	
	for(int i=0; i<n; i++)
		vec.push_back(alfa*x[i]);
	
	return vec;
}

//Funcion norma 1
double norma1(vector<double> x){
	int n=x.size();
	double res=0;
	
	for(int i=0; i<n; i++){
		res+=abs(x[i]);
	}
	
	return res;
}

// Funcion que varia el nu radio con las iteraciones
double nuRadioVariable(double ite, double limSup, double limInf, double max_epocas){
	return limSup - (limSup-limInf)*ite/max_epocas;
}


void graficarEntradas(mdouble entradas, vector<int> salidas){
	
	int canEntradas = entradas.size();
	double x,y;
	vector<double>::iterator p;
	
	glColor3f(0,1,0);
	glBegin(GL_LINES);
	glVertex2f(-2,0);
	glVertex2f(2,0);
	glVertex2f(0,-2);
	glVertex2f(0,2);
	glEnd();
	
	glPointSize(3.0);
	glBegin(GL_POINTS);
	
	for (int i=0;i<canEntradas;i++){
		glColor3f(1,0,0);
		if(salidas[i]==1)
			glColor3f(0,1,0);
		p=entradas[i].begin();
		x=*p;p++;y=*p;
		glVertex2f(x,y);
	}
	glEnd();
	
}
