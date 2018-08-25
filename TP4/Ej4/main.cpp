

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

typedef vector<vector<double> > mdouble;
typedef vector<double> vdouble;
typedef mdouble::iterator itm;
typedef vector<int> vint;
typedef vector<double>::iterator itv;

// ***************** VARIABLES GLOBALES *****************

mdouble entradas,salidasD;
vdouble salidasAux;
vint capas;

int w=800,h=600,op=2;

#include "readFile.h"
#include "funcionesAux.h"
#include "particula.h"
#include "enjambre.h"

Enjambre enja;


void dibRectas(){
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(.0,1.0,.0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(500,0);
	glVertex2f(0,0);
	glVertex2f(0,500);
	
	float pos=0,ap=0.05,alto=.01;
	// eje x
	while(pos<1){
		glVertex2f(pos,-alto);
		glVertex2f(pos,alto);
		pos+=ap;
	}
	pos=0;
	// eje y
	while(pos<1){
		glVertex2f(-alto,pos);
		glVertex2f(alto,pos);
		pos+=ap;
	}
	glEnd();
	glPopAttrib();
}

void display_cb() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,1); glLineWidth(3);
	glPointSize(4);
	glLineWidth(1);
	glPushMatrix();
		glTranslated(10,10,0);
		glScaled(900,900,1);
		dibRectas();
		enja.dibIteracion();
		glColor3f(.0,0.,0.);
	glPopMatrix();
	glutSwapBuffers();
}

void reshape_cb (int w, int h) {
	if (w==0||h==0) return;
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0,w,0,h);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}




void Special_cb(int key, int xm=0, int im=0){
	if(key ==GLUT_KEY_F1)
		exit(EXIT_SUCCESS);
}


void Keyboard_cb(unsigned char key,int xx=0,int yy=0) {	
	switch(key){
	case 'q':{
		enja.evaluarTodos();
		//enja.showMatricesPesos();
		break;
	}
	case 'v':{
		enja.showMatricesPesos();
		break;}
	}
	display_cb();
}

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (w,h);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Ventana OpenGL");
	glutDisplayFunc (display_cb);
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);
	glutKeyboardFunc(Keyboard_cb);
	glutSpecialFunc(Special_cb);
}

int main (int argc, char **argv) {
	srand(time(NULL));
	
	//***************** Inicializamos las entradas y salidas *******************
	Operacion(op);

	
	int posSize=0;
	for(int i=1;i<capas.size(); i++){
		posSize+=(capas[i-1]*capas[i]);
	}
	
	// *************************************************************************
	
	
	enja=Enjambre(20,posSize);
	
	glutInit (&argc, argv);
	initialize();
	glutMainLoop();
	return 0;
}
