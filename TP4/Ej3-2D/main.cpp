

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#include "particula.h"
#include "enjambre.h"


// ***************** VARIABLES GLOBALES *****************
Enjambre enja;

int w=800,h=750;

void dibCurba(){
	glBegin(GL_LINES);
		for(float i=-500;i<501;i++){
			glVertex2f(i,-i*sin(sqrt(abs(i))));
			glVertex2f(i+1,-(i+1)*sin(sqrt(abs(i+1))));
		}
	glEnd();
}

void dibRectas(){
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(.0,1.0,.0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(-500,0);
	glVertex2f(500,0);
	glVertex2f(0,-500);
	glVertex2f(0,500);
	
	float pos=-500,ap=1000/20.0;
	// eje x
	for(int i=0;i<21;i++){
		glVertex2f(pos+ap*i,-10);
		glVertex2f(pos+ap*i,10);
	}
	// eje y
	for(int i=0;i<21;i++){
		glVertex2f(-10,pos+ap*i);
		glVertex2f(10,pos+ap*i);
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
		
		glTranslated(w/2,h/2,0);
		glScaled(0.5,0.5,1);
		dibRectas();
		enja.dibEnjambre();
		glColor3f(1.0,0.,0.);
		dibCurba();
		
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
		break;
	}
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
	
	enja=Enjambre(20,1);
	
	glutInit (&argc, argv);
	initialize();
	glutMainLoop();
	return 0;
}
