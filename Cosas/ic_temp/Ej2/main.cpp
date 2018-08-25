#include <GL/glut.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

// librerias calcular el tiempo que tarda
#include <ctime>

clock_t startC, finishC;


using namespace std;

#include "funcionesAux.h"
#include "individuo.h"
#include "poblacion.h"

poblacion poblado;
int funcion=2;

vector<vector<double> > D;

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
	glColor3f(0,0,0); 
	glPointSize(3);
	glLineWidth(1);
	glPushMatrix();
		if(funcion==1){
			glTranslated(650,350,0);
			glScaled(0.7,0.7,1);}
		if(funcion==2){
			glTranslated(300,150,0);	
			glScaled(15,13,1);
		}
		// dibugar
		dibPuntos(funcion);
		poblado.dibPoblacion();
	glPopMatrix();
	
	glutSwapBuffers();
}

void Keyboard_cb(unsigned char key,int xx=0,int yy=0) {	
	switch(key){
	case 'q':{
		poblado.selectProgenitores(20);
		poblado.mezclarProgenitores();
		
		break;
		}
	case 'b':{
		poblado.showBest(funcion);
		break;
		}
	case 'w':{
		startC = clock();
		for(int i=0;i<1000;i++){
			poblado.selectProgenitores(20);
			poblado.mezclarProgenitores();
		}
		poblado.showBest(funcion);
		finishC = clock();
		cout << "Time (difftime): " << difftime(finishC, startC)/1000000.0<< endl;
		break;
	}
	default:{
		break;
		}
	}
	display_cb();
}

void Special_cb(int key, int xm=0, int im=0){
	if(key ==GLUT_KEY_F1)
		exit(EXIT_SUCCESS);
}

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (1300,750);
	glutInitWindowPosition (20,10);
	glutCreateWindow ("Algoritmo Genetico");
	glutDisplayFunc (display_cb);
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);
	glutKeyboardFunc(Keyboard_cb);
	glutSpecialFunc(Special_cb);
}

int main (int argc, char **argv) {
	// *** aca se arma la matriz D (puede ser con numeros aleatorios positivos)
	// *** la diagonal es cero, matriz simetrica
	
	// dimensiona la matriz a 10x10
	vector<double>::iterator it;
	
	D.resize(10);
	for(it=D.begin();it<D.end();it++)
		*it.resize(10);
	
	// arma la matriz
	for(int i=0; i<D.size();i++){
		for(int j=i; j<D[i].size();j++){
			// diagonal cero
			if(i==j)
				D[i][j]=0;
			
			// distancia aleatoria
			D[i][j]=10*rand()/RAND_MAX;
			
			// simetria
			D[j][i]=D[i][j];
		}
	}
	
	// *** ver el tema de controlar que no repita ciudades y que cuando recorra
	//todas, vuelva a la inicial
	
	// *** ver el tema de la funcion de fitness, ya que hay que comparar la
	//distancia calculada con una distancia de la matriz
	
	srand(time(NULL));
	int cantPobla=100, cantGene=9;
	
	if(funcion==2)
		cantGene=30;
	poblado = poblacion(cantPobla,cantGene,funcion);
	
	poblado.mostrarTodo();
	
	glutInit (&argc, argv);
	initialize();
	glutMainLoop();
	cin.get();
	return 0;
}
