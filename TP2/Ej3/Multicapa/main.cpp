#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>



using namespace std;

typedef vector<vector<double> > mdouble;
typedef vector<double> vdouble;
typedef mdouble::iterator itm;
typedef vector<int> vint;
typedef vector<double>::iterator itv;

vdouble ww;
int iteRand=0;


#include "funciones.h"
#include "Readfile.h"
#include "Capa.h"
#include "Red.h"


// Definimos las variables
vint neuronas;
mdouble entradas,ydeseada;
vdouble salidas,yd;
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
	glPushMatrix();
		glTranslated(400,350,0);
		glScaled(100,100,1);
		redd.dibPuntos(salidas,entradas,opcion);
		redd.dibPesos(opcion);
	glPopMatrix();
	
	glutSwapBuffers();
}


void Special_cb(int key, int xm=0, int im=0){
	if(key ==GLUT_KEY_F1)
		exit(EXIT_SUCCESS);
	
}

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (800,700);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("PruebaCoulds");
	glutDisplayFunc (display_cb);
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);
	glutSpecialFunc(Special_cb);
}

int main (int argc, char **argv) {
	
	
	// Leemos la base de datos
	readFile(entradas,salidas,"clouds.csv",true);
	//readFile(entradas,salidas,"phoneme.csv",true);
	opcion=2;
	// Asignamos la cantidad de neuronas para cada capa
//		neuronas.push_back(3);
	neuronas.push_back(10);
	neuronas.push_back(6);
	neuronas.push_back(2);
	
	int cantEntradas = entradas[0].size(),cantDatos=entradas.size();
	
	vdouble aux;
	aux.push_back(-1);
	aux.push_back(-1);
	
	
	
	for(int i=0;i<cantDatos;i++){
		if(salidas[i]==0.0){
			ydeseada.push_back(aux);
			ydeseada[i][0]=1;
		}
		if(salidas[i]==1.0){
			ydeseada.push_back(aux);
			ydeseada[i][1]=1;
		}
	}
	
	// Creamos la red
	redd = Red(neuronas, cantEntradas);
	
	cout<<"Comenzando entrenamiento con "<<cantEntradas<<" entradas y "
		<<cantDatos<<" cantidad de datos"<<endl;
	
	cout<<"Pesos iniciales"<<endl;
	redd.showPesos();	
	cout<<endl;
	
	
	for(int j=0;j<500;j++){
		for (int i=0;i<cantDatos;i++){
			redd.propagacion(entradas[i]);
			redd.retropopagacion(ydeseada[i],entradas[i]);
		}
		double aciertos=redd.pruebaIris(ydeseada,entradas);
		cout<< "Acertados:  "<<aciertos<<"%"<<endl;
		if(aciertos>86){
			cout<<"Epocas completadas:  "<<j+1<<endl;
			cout<<endl;
			j=100000000;
			}
		
	}
	cout<<"Pesos Finales"<<endl;
	redd.showPesos();
	
	cout<<"Pesos finales guardados"<<endl;
	redd.savePeso();
	
	glutInit (&argc, argv);
	initialize();
	glutMainLoop();
	return 0;
}
