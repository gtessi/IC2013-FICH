#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

// Definicion de los tipos de dattos
typedef vector<double> vdouble;
typedef vector<vector<double> > mdouble;

// Incluimos las librerias propias
#include "funcionesAux.h"
#include "Readfile.h"
#include "centroide.h"
#include "cenVector.h"

// Definimos algunas variables globales
int iteRand=0,ePos=0;
mdouble entradas;
vdouble salidas;
CenVector centroides;


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
		glTranslated(320.0,240.0,0);
		glScaled(200.0,200.0,1);
		glLineWidth(3.0);
		glColor3f(.0,1.0,.0);
		glBegin(GL_LINES);
			glVertex2d(.0,2.0);
			glVertex2d(.0,-2.0);
			glVertex2d(-2.0,.0);
			glVertex2d(2.0,.0);
		glEnd();
		
		glColor3f(.0,.0,1.0);
		plotM2D(entradas);
		centroides.plotCent();
	glPopMatrix();
	
	glutSwapBuffers();
}

void Keyboard_cb(unsigned char key,int xx=0,int yy=0) {
	
	switch (key){
	case 'a':{
		centroides.actualizar(entradas);
		break;
	}
	case 's':{
		centroides.actualizarPaso(entradas[ePos]);
		ePos= (++ePos)%entradas.size();
		break;
	}
	case 'd':{
		centroides.calcularDV(entradas);
		break;
	}
	default:
		cout<<"hola"<<endl;
	}
	
	display_cb();
}

void Special_cb(int key, int xm=0, int im=0){
	if(key ==GLUT_KEY_F1)
		exit(EXIT_SUCCESS);
	
}

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (640,480);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Ventana OpenGL");
	glutDisplayFunc (display_cb);
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);
	glutSpecialFunc(Special_cb);
	glutKeyboardFunc (Keyboard_cb);
}

int main (int argc, char **argv) {
	
	
	readFile(entradas,salidas,"entradasXORsinBias2.txt",false);
	
	int datoSize = entradas.size(), eSize=entradas[0].size();
	
	centroides = CenVector(4,eSize);

	glutInit (&argc, argv);
	initialize();
	glutMainLoop();
	return 0;
}
