#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <time.h>



using namespace std;

typedef vector<vector<double> > mdouble;
typedef vector<double> vdouble;
typedef mdouble::iterator itm;
typedef vector<int> vint;
typedef vector<double>::iterator itv;

vdouble ww;
int iteRand=0;


#include "funciones.h"
#include "Capa.h"
#include "Red.h"
#include "Readfile.h"

// Definimos las variables
vint neuronas; //Vector de neuronas
mdouble entradas, entradas_ent, entradas_pru;//Matriz de entradas
vdouble salidas, salidas_ent, salidas_pru,yd;//Vector de Salidas y de Salida deseada
Red redd;
bool equisOR;
int opcion=1;



void reshape_cb (int w, int h) {
	if (w==0||h==0) return;
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0,w,0,h);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void display_cb() {
	glClear(GL_COLOR_BUFFER_BIT);
	redd.dibPuntos(salidas,entradas,opcion);
	redd.dibPesos(opcion);
	glutSwapBuffers();
}


void Special_cb(int key, int xm=0, int im=0){
	if(key ==GLUT_KEY_F1)
		exit(EXIT_SUCCESS);
	
}

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (640,480);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Ejercicio 4");
	glutDisplayFunc (display_cb);
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);
	glutSpecialFunc(Special_cb);
}

int main (int argc, char **argv) {
	
	bool xxor=false;//Bandera, True: Archivo "entradasXOR"
//								False: Archivo "concent2.csv"
	
	if(xxor){
		readFile(entradas,salidas,"entradasXOR.txt",false);//Leer archivo
		opcion=1;
		
		// Asignamos la cantidad de neuronas para cada capa
		neuronas.push_back(2);
		neuronas.push_back(1);
		
	}else{
		
		// Leemos la base de datos
		readFile(entradas,salidas,"concent2.csv",true);
		opcion=2;
		// Asignamos la cantidad de neuronas para cada capa
//		neuronas.push_back(3);
//		neuronas.push_back(2);
		neuronas.push_back(4);
		neuronas.push_back(3);
		neuronas.push_back(1);
		
	}
	
	//PARTICIONAR 80/20
	particionar_matriz(entradas,80,entradas_ent,entradas_pru);
	particionar_vector(salidas,80,salidas_ent,salidas_pru);
	
	int cantEntradas = entradas_ent[0].size(); //Cantidad de entradas
	int cantDatos=entradas_ent.size(); //Cantidad de ejemplos de las entradas
	
	
	redd = Red(neuronas, cantEntradas);//Se crea la Red 
	
	cout<<"Comenzando entrenamiento con "<<cantEntradas<<" entradas y "
		<<cantDatos<<" cantidad de datos"<<endl<<endl;
	
	system("pause");
	
	cout<<endl;
	cout<<" Pesos iniciales"<<endl;
	cout<<"-----------------"<<endl;
	redd.showPesos();	
	cout<<endl;
	
	system("pause");
	
	bool bandera_corte=true;//Bandera de corte por epocas
	int canti_epocas=300;//Cantidad de epocas para entrenar
	for(int j=0;j<canti_epocas;j++){//Para canti_epocas recorro...
		for (int i=0;i<cantDatos;i++){//Para cada dato propago y retropopago.
			redd.propagacion(entradas_ent[i]);//Propagamos para cada dato
			yd.push_back(salidas_ent[i]);//Guardamos en Yd la salida deseada
			redd.retropopagacion(yd,entradas_ent[i]);//Retropopagacion. Luego actualizacion de pesos
			yd.clear();//Borro Yd (Salida Deseada)
		}
		
		double aciertos=redd.prueba(salidas_ent,entradas_ent);
		cout<< "Acertados:  "<<aciertos<<"%"<<"   epoca:"<<j+1<<endl;
		if(aciertos>93){//Tolerancia de aciertos
			cout<<"Epocas completadas:  "<<j+1<<endl;
			cout<<endl;
			j=100000000;//Como debe salir por aciertos, entonces hacemos que j=10000 y salga del for
			bandera_corte=false;
			cout<<endl<<endl<<" ***Corte: Por Tolerancia*** "<<endl<<endl;
			system("pause");
			}
		
	}
	
	if(bandera_corte) {
		cout<<endl<<endl<<" ***Corte: Por Epocas*** "<<endl<<endl;
		system("pause");
	}
	
	
	cout<<" Pesos Finales"<<endl;
	cout<<"-----------------"<<endl;
	redd.showPesos();	
	system("pause");
	
	cout<<endl<<"**************"<<endl;
	cout<<"Incia Prueba"<<endl;
	cout<<"**************"<<endl;
	//Realiza la prueba con entradas_pru y salidas_pru, o sea el 20%
	double conta=0;
	for(int i=0; i<entradas_pru.size(); i++){
		conta+=redd.prueba(salidas_pru,entradas_pru);		
	}
	cout<< "Acertados:  "<<conta/entradas_pru.size()<<"%"<<endl;
	
	
	
	
	cout<<endl<<"Graficar...."<<endl;
	system("pause");
	
	glutInit (&argc, argv);
	initialize();
	glutMainLoop();
	return 0;
}
