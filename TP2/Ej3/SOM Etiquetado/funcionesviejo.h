#include <cmath>
#include <algorithm>

using namespace std;

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
	double min =-.5,max=.5;
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



